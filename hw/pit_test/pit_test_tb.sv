`timescale 1ns / 1ps
`default_nettype none

// Stress test bench for the ECEN 427 PIT (module pit_sv in hw/ip_repo/pit/pit.sv).
//
// This test bench instantiates pit_sv directly and drives it with its own
// AXI4-Lite master, rather than the Xilinx AXI VIP.  The VIP's default timing
// is forgiving: AW and W arrive in the same cycle, addresses and data stay on
// the bus after the handshake, BREADY/RREADY are often already high, and
// transactions are spaced apart.  The ARM CPU and the AXI interconnect in the
// real system do none of these things, so a PIT can pass a VIP test bench and
// still hang or misbehave in hardware.  This master:
//   * asserts AWVALID and WVALID in either order, with random gaps between them;
//   * drives the *other* register's address and inverted data onto the bus as
//     soon as each handshake completes (catching slaves that sample too late);
//   * raises BREADY/RREADY either before VALID or only some cycles after it;
//   * issues back-to-back transactions, and reads concurrently with writes.
// A protocol monitor checks the slave's side of every handshake, and the
// functional tests check the register and timer behavior in the lab spec.
//
// Run with `make test_pit` in the hw directory (pit_test/run_pit_test.tcl).  The last line printed is either
// "PIT TEST RESULT: ALL TESTS PASSED" or "PIT TEST RESULT: FAILED".

module pit_test_tb;

  localparam logic [3:0] ADDR_CTRL  = 4'h0;
  localparam logic [3:0] ADDR_DELAY = 4'h4;
  localparam logic [31:0] RESET_CTRL  = 32'd3;
  localparam logic [31:0] RESET_DELAY = 32'd1666667;
  localparam logic [1:0] RESP_OKAY = 2'b00;

  // Cycles to wait on any handshake before declaring a deadlock.  In
  // hardware, a deadlocked AXI slave hangs the CPU.
  localparam int TIMEOUT = 100;
  // Tolerance (cycles) when comparing interrupt times against a write's
  // handshake, to allow for a slave that commits a write a cycle or two late.
  localparam int GRACE = 2;

  ///////////////////////////////////////////////////////////////////////////
  // Clock, reset, DUT
  ///////////////////////////////////////////////////////////////////////////
  logic clk = 1'b0;
  logic resetn = 1'b0;
  always #5 clk = ~clk;

  logic        awvalid = 1'b0;
  logic        awready;
  logic [3:0]  awaddr  = '0;
  logic [2:0]  awprot  = '0;
  logic        wvalid  = 1'b0;
  logic        wready;
  logic [31:0] wdata   = '0;
  logic [3:0]  wstrb   = 4'hf;
  logic        bvalid;
  logic        bready  = 1'b0;
  logic [1:0]  bresp;
  logic        arvalid = 1'b0;
  logic        arready;
  logic [3:0]  araddr  = '0;
  logic [2:0]  arprot  = '0;
  logic [31:0] rdata;
  logic [1:0]  rresp;
  logic        rvalid;
  logic        rready  = 1'b0;
  logic        irq;

  pit_sv #(.C_S_AXI_ADDR_WIDTH(4)) dut (
    .s_axi_aclk(clk),
    .s_axi_aresetn(resetn),
    .s_axi_awvalid(awvalid),
    .s_axi_awready(awready),
    .s_axi_awaddr(awaddr),
    .s_axi_awprot(awprot),
    .s_axi_wvalid(wvalid),
    .s_axi_wready(wready),
    .s_axi_wdata(wdata),
    .s_axi_wstrb(wstrb),
    .s_axi_bvalid(bvalid),
    .s_axi_bready(bready),
    .s_axi_bresp(bresp),
    .s_axi_arvalid(arvalid),
    .s_axi_arready(arready),
    .s_axi_araddr(araddr),
    .s_axi_arprot(arprot),
    .s_axi_rdata(rdata),
    .s_axi_rresp(rresp),
    .s_axi_rvalid(rvalid),
    .s_axi_rready(rready),
    .irq(irq)
  );

  // Edge counter.  Every process samples it right after a rising edge, so
  // all of them see the same value for the same edge.
  int unsigned cycle = 0;
  always @(posedge clk) cycle <= cycle + 1;

  ///////////////////////////////////////////////////////////////////////////
  // Error reporting
  ///////////////////////////////////////////////////////////////////////////
  int errors = 0;
  int test_errors = 0;
  int tests_passed = 0;
  int tests_failed = 0;
  string test_name = "setup";

  function automatic void error(string msg);
    errors++;
    test_errors++;
    if (errors <= 60)
      $display("[%0t] ERROR (%s): %s", $time, test_name, msg);
    else if (errors == 61)
      $display("[%0t] ... further errors suppressed", $time);
  endfunction

  // Problems that are not counted as failures.
  int warnings = 0;

  function automatic void warn(string msg);
    warnings++;
    if (warnings <= 5)
      $display("[%0t] WARNING (%s): %s", $time, test_name, msg);
    else if (warnings == 6)
      $display("[%0t] ... further warnings suppressed", $time);
  endfunction

  task automatic begin_test(string name);
    test_name = name;
    test_errors = 0;
    $display("\n=== %s ===", name);
  endtask

  task automatic end_test();
    if (test_errors == 0) begin
      tests_passed++;
      $display("PASS: %s", test_name);
    end else begin
      tests_failed++;
      $display("FAIL: %s (%0d errors)", test_name, test_errors);
    end
  endtask

  task automatic finish_sim();
    $display("\n==================================================");
    $display("Tests passed: %0d, tests failed: %0d, total errors: %0d, warnings: %0d",
             tests_passed, tests_failed, errors, warnings);
    if (errors == 0 && tests_failed == 0)
      $display("PIT TEST RESULT: ALL TESTS PASSED");
    else
      $display("PIT TEST RESULT: FAILED");
    $finish;
  endtask

  // A handshake never completed.  Nothing after this point is meaningful.
  task automatic deadlock(string msg);
    error({"DEADLOCK: ", msg, " (in hardware this hangs the CPU)"});
    tests_failed++;
    $display("FAIL: %s (stopped: deadlock)", test_name);
    finish_sim();
  endtask

  function automatic string regname(logic [3:0] addr);
    return (addr == ADDR_CTRL) ? "control" : "delay-value";
  endfunction

  ///////////////////////////////////////////////////////////////////////////
  // irq monitor: records the edge at which each irq pulse starts, and checks
  // that every pulse is exactly one cycle wide.
  ///////////////////////////////////////////////////////////////////////////
  int unsigned irq_starts[$];
  logic irq_prev = 1'b0;
  bit irq_x_reported = 0;

  always @(posedge clk) begin
    if (!resetn) begin
      irq_prev <= 1'b0;
    end else begin
      if ($isunknown(irq)) begin
        if (!irq_x_reported) error("irq is X/Z after reset");
        irq_x_reported = 1;
      end else if (irq) begin
        if (irq_prev) error("irq stayed high for more than one cycle");
        else irq_starts.push_back(cycle);
      end
      irq_prev <= (irq === 1'b1);
    end
  end

  function automatic int count_irqs(int unsigned from, int unsigned to);
    int n = 0;
    foreach (irq_starts[i])
      if (irq_starts[i] >= from && irq_starts[i] <= to) n++;
    return n;
  endfunction

  // Wait for the first irq pulse that starts after edge `after`, giving up
  // max_wait cycles after `after`.
  task automatic wait_irq_after(input int unsigned after, input int max_wait,
                                output int unsigned t, output bit ok);
    int idx[$];
    ok = 0;
    t = 0;
    forever begin
      idx = irq_starts.find_first_index(x) with (x > after);
      if (idx.size() > 0) begin
        t = irq_starts[idx[0]];
        ok = 1;
        return;
      end
      if (cycle > after + max_wait + 1) return;
      @(posedge clk);
    end
  endtask

  // Wait for the irq pulse after the one at edge `prev` and check that it
  // starts exactly n cycles later.
  task automatic expect_period(input int unsigned prev, input int n, input string what,
                               output int unsigned t);
    bit ok;
    int gap;
    wait_irq_after(prev, n + 10, t, ok);
    if (!ok) begin
      error($sformatf("%s: no irq within %0d cycles", what, n + 10));
    end else begin
      gap = t - prev;
      if (gap != n)
        error($sformatf("%s: irq came %0d cycles after the previous one, expected %0d", what, gap, n));
    end
  endtask

  task automatic wait_until_cycle(int unsigned c);
    while (cycle < c) @(posedge clk);
  endtask

  ///////////////////////////////////////////////////////////////////////////
  // AXI protocol monitor (checks the slave's side of the bus)
  ///////////////////////////////////////////////////////////////////////////
  int aw_hs = 0, w_hs = 0, b_hs = 0, ar_hs = 0, r_hs = 0;
  logic prev_bvalid = 1'b0, prev_bready = 1'b0, prev_rvalid = 1'b0, prev_rready = 1'b0;
  logic [1:0]  prev_bresp, prev_rresp;
  logic [31:0] prev_rdata;
  bit reported[string];

  function automatic void error_once(string key, string msg);
    if (!reported.exists(key)) begin
      reported[key] = 1;
      error(msg);
    end
  endfunction

  always @(posedge clk) begin
    if (!resetn) begin
      aw_hs = 0; w_hs = 0; b_hs = 0; ar_hs = 0; r_hs = 0;
      prev_bvalid = 1'b0; prev_bready = 1'b0;
      prev_rvalid = 1'b0; prev_rready = 1'b0;
    end else begin
      bit aw_now, w_now, b_now, ar_now, r_now;

      if ($isunknown(awready)) error_once("awx", "s_axi_awready is X/Z after reset");
      if ($isunknown(wready))  error_once("wx",  "s_axi_wready is X/Z after reset");
      if ($isunknown(bvalid))  error_once("bx",  "s_axi_bvalid is X/Z after reset");
      if ($isunknown(arready)) error_once("arx", "s_axi_arready is X/Z after reset");
      if ($isunknown(rvalid))  error_once("rx",  "s_axi_rvalid is X/Z after reset");

      aw_now = awvalid && (awready === 1'b1);
      w_now  = wvalid  && (wready  === 1'b1);
      b_now  = (bvalid === 1'b1) && bready;
      ar_now = arvalid && (arready === 1'b1);
      r_now  = (rvalid === 1'b1) && rready;

      if (bvalid === 1'b1) begin
        if ($isunknown(bresp)) error("s_axi_bresp is X/Z while s_axi_bvalid is high");
        if (b_hs >= aw_hs + aw_now || b_hs >= w_hs + w_now)
          error("s_axi_bvalid asserted before both the AW and W handshakes of a write completed");
      end
      if (rvalid === 1'b1) begin
        if ($isunknown(rdata)) error("s_axi_rdata is X/Z while s_axi_rvalid is high");
        if ($isunknown(rresp)) error("s_axi_rresp is X/Z while s_axi_rvalid is high");
        if (r_hs >= ar_hs + ar_now)
          error("s_axi_rvalid asserted without an outstanding read (no AR handshake)");
      end

      // Once VALID is high, it and its payload must hold until READY.
      if (prev_bvalid && !prev_bready) begin
        if (bvalid !== 1'b1)
          error("s_axi_bvalid dropped before s_axi_bready was seen (VALID must stay high until the handshake)");
        else if (bresp !== prev_bresp)
          error("s_axi_bresp changed while waiting for s_axi_bready");
      end
      if (prev_rvalid && !prev_rready) begin
        if (rvalid !== 1'b1)
          error("s_axi_rvalid dropped before s_axi_rready was seen (VALID must stay high until the handshake)");
        else if (rresp !== prev_rresp)
          error("s_axi_rresp changed while waiting for s_axi_rready");
        else if (rdata !== prev_rdata)
          // An AXI violation, but in practice the CPU just reads the old or
          // new register value, so this is only a warning.
          warn({"s_axi_rdata changed while s_axi_rvalid was waiting for s_axi_rready ",
                "(AXI requires it to hold; capture the read data at the AR handshake)"});
      end

      aw_hs += aw_now; w_hs += w_now; b_hs += b_now;
      ar_hs += ar_now; r_hs += r_now;
      prev_bvalid = (bvalid === 1'b1);
      prev_bready = bready;
      prev_bresp  = bresp;
      prev_rvalid = (rvalid === 1'b1);
      prev_rready = rready;
      prev_rdata  = rdata;
      prev_rresp  = rresp;
    end
  end

  ///////////////////////////////////////////////////////////////////////////
  // AXI4-Lite master
  ///////////////////////////////////////////////////////////////////////////

  // Random delay before asserting a VALID or READY: often 0, sometimes long.
  function automatic int rand_delay();
    int r = $urandom_range(0, 99);
    if (r < 45) return 0;
    if (r < 80) return $urandom_range(1, 3);
    return $urandom_range(4, 15);
  endfunction

  // B/R ready policy: -2 = READY high before VALID; >= 0 = READY raised
  // that many cycles after VALID is seen.
  function automatic int rand_ready_policy();
    return ($urandom_range(0, 1) == 0) ? -2 : rand_delay();
  endfunction

  // Edge at which the most recent write was accepted (the later of its AW
  // and W handshakes).
  int unsigned last_accept;

  // One AXI4-Lite write.  aw_delay/w_delay: cycles before raising each VALID
  // (-1 = random).  b_policy: see rand_ready_policy (-1 = random).
  task automatic axi_write(input logic [3:0] addr, input logic [31:0] data,
                           input int aw_delay = -1, input int w_delay = -1,
                           input int b_policy = -1);
    int unsigned aw_cycle = 0, w_cycle = 0;
    bit ok_aw = 0, ok_w = 0, ok_b = 0, b_seen = 0;
    logic [1:0] resp;
    if (aw_delay < 0) aw_delay = rand_delay();
    if (w_delay < 0)  w_delay  = rand_delay();
    if (b_policy == -1) b_policy = rand_ready_policy();

    fork
      begin : aw_channel
        int n = 0;
        repeat (aw_delay) @(posedge clk);
        awaddr  <= addr;
        awprot  <= 3'b000;
        awvalid <= 1'b1;
        do begin @(posedge clk); n++; end while (awready !== 1'b1 && n <= TIMEOUT);
        if (awready === 1'b1) begin ok_aw = 1; aw_cycle = cycle; end
        // Handshake done: put the wrong address on the bus immediately.
        awvalid <= 1'b0;
        awaddr  <= addr ^ 4'h4;
        awprot  <= 3'b111;
      end
      begin : w_channel
        int n = 0;
        repeat (w_delay) @(posedge clk);
        wdata  <= data;
        wstrb  <= 4'hf;
        wvalid <= 1'b1;
        do begin @(posedge clk); n++; end while (wready !== 1'b1 && n <= TIMEOUT);
        if (wready === 1'b1) begin ok_w = 1; w_cycle = cycle; end
        wvalid <= 1'b0;
        wdata  <= ~data;
      end
      begin : b_channel
        int n = 0;
        if (b_policy == -2) bready <= 1'b1;
        do begin @(posedge clk); n++; end
        while (bvalid !== 1'b1 && n <= TIMEOUT + 2 * 15);
        if (bvalid === 1'b1) begin
          b_seen = 1;
          if (b_policy >= 0) begin
            repeat (b_policy) @(posedge clk);
            bready <= 1'b1;
            n = 0;
            do begin @(posedge clk); n++; end while (bvalid !== 1'b1 && n <= TIMEOUT);
          end
          if (bvalid === 1'b1) begin ok_b = 1; resp = bresp; end
        end
        bready <= 1'b0;
      end
    join

    if (!ok_aw) deadlock($sformatf("s_axi_awready never asserted for a write to %s", regname(addr)));
    if (!ok_w)  deadlock($sformatf("s_axi_wready never asserted for a write to %s", regname(addr)));
    if (!ok_b) begin
      if (!b_seen && b_policy >= 0)
        deadlock($sformatf({"s_axi_bvalid never asserted for a write to %s while s_axi_bready was low.  ",
                            "The slave must not wait for BREADY before asserting BVALID"}, regname(addr)));
      else
        deadlock($sformatf("s_axi_bvalid never asserted for a write to %s", regname(addr)));
    end
    if (resp !== RESP_OKAY)
      error($sformatf("write to %s returned s_axi_bresp = %b, expected OKAY (00)", regname(addr), resp));
    last_accept = (aw_cycle > w_cycle) ? aw_cycle : w_cycle;
  endtask

  // One AXI4-Lite read.  ar_delay: cycles before raising ARVALID (-1 = random).
  // r_policy: see rand_ready_policy (-1 = random).
  task automatic axi_read(input logic [3:0] addr, output logic [31:0] data,
                          input int ar_delay = -1, input int r_policy = -1);
    bit ok_ar = 0, ok_r = 0, r_seen = 0;
    logic [1:0] resp;
    if (ar_delay < 0) ar_delay = rand_delay();
    if (r_policy == -1) r_policy = rand_ready_policy();
    data = 'x;

    fork
      begin : ar_channel
        int n = 0;
        repeat (ar_delay) @(posedge clk);
        araddr  <= addr;
        arprot  <= 3'b000;
        arvalid <= 1'b1;
        do begin @(posedge clk); n++; end while (arready !== 1'b1 && n <= TIMEOUT);
        if (arready === 1'b1) ok_ar = 1;
        arvalid <= 1'b0;
        araddr  <= addr ^ 4'h4;
        arprot  <= 3'b111;
      end
      begin : r_channel
        int n = 0;
        if (r_policy == -2) rready <= 1'b1;
        do begin @(posedge clk); n++; end
        while (rvalid !== 1'b1 && n <= TIMEOUT + 15);
        if (rvalid === 1'b1) begin
          r_seen = 1;
          if (r_policy >= 0) begin
            repeat (r_policy) @(posedge clk);
            rready <= 1'b1;
            n = 0;
            do begin @(posedge clk); n++; end while (rvalid !== 1'b1 && n <= TIMEOUT);
          end
          if (rvalid === 1'b1) begin ok_r = 1; data = rdata; resp = rresp; end
        end
        rready <= 1'b0;
      end
    join

    if (!ok_ar) deadlock($sformatf("s_axi_arready never asserted for a read of %s", regname(addr)));
    if (!ok_r) begin
      if (!r_seen && r_policy >= 0)
        deadlock($sformatf({"s_axi_rvalid never asserted for a read of %s while s_axi_rready was low.  ",
                            "The slave must not wait for RREADY before asserting RVALID"}, regname(addr)));
      else
        deadlock($sformatf("s_axi_rvalid never asserted for a read of %s", regname(addr)));
    end
    if (resp !== RESP_OKAY)
      error($sformatf("read of %s returned s_axi_rresp = %b, expected OKAY (00)", regname(addr), resp));
  endtask

  ///////////////////////////////////////////////////////////////////////////
  // Register model and checked accesses
  ///////////////////////////////////////////////////////////////////////////
  // Only bits [1:0] of the control register are checked; the spec lets
  // students use the other bits as they see fit.
  logic [31:0] model_ctrl  = RESET_CTRL;
  logic [31:0] model_delay = RESET_DELAY;

  function automatic logic [31:0] model(logic [3:0] addr);
    return (addr == ADDR_CTRL) ? model_ctrl : model_delay;
  endfunction

  function automatic bit value_ok(logic [3:0] addr, logic [31:0] got, logic [31:0] expected);
    if (addr == ADDR_CTRL) return got[1:0] === expected[1:0];
    return got === expected;
  endfunction

  task automatic reg_write(input logic [3:0] addr, input logic [31:0] data,
                           input int aw_delay = -1, input int w_delay = -1,
                           input int b_policy = -1);
    axi_write(addr, data, aw_delay, w_delay, b_policy);
    if (addr == ADDR_CTRL) model_ctrl = data;
    else model_delay = data;
  endtask

  task automatic check_read(input logic [3:0] addr, input string what,
                            input int ar_delay = -1, input int r_policy = -1);
    logic [31:0] got;
    axi_read(addr, got, ar_delay, r_policy);
    if (!value_ok(addr, got, model(addr)))
      error($sformatf("%s: read %s = %0d (0x%08h), expected %0d (0x%08h)%s", what,
                      regname(addr), got, got, model(addr), model(addr),
                      (addr == ADDR_CTRL) ? " [only bits 1:0 are checked]" : ""));
  endtask

  // Writes with short, random VALID delays, for tests that measure timing.
  task automatic timed_write(input logic [3:0] addr, input logic [31:0] data);
    reg_write(addr, data, $urandom_range(0, 3), $urandom_range(0, 3), -1);
  endtask

  // Stop the timer and start it with period n.
  task automatic start_timer(int n);
    reg_write(ADDR_CTRL, 0);
    reg_write(ADDR_DELAY, n);
    timed_write(ADDR_CTRL, 3);
  endtask

  ///////////////////////////////////////////////////////////////////////////
  // Tests
  ///////////////////////////////////////////////////////////////////////////
  initial begin
    // Global watchdog
    #20ms;
    error("global simulation timeout");
    finish_sim();
  end

  initial run_tests();

  task automatic run_tests();
    int unsigned t0, t1, t, t_dis, t_en, t_prev;
    bit ok;
    logic [31:0] d;
    int periods[] = '{4, 2, 3, 7, 16};
    int ctrl_vals[] = '{1, 2, 3, 0};
    logic [31:0] delay_vals[] = '{32'd5, 32'hFFFF_FFFF, 32'h8000_0001, 32'h1234_5678, 32'd1666667, 32'd4};
    int gaps[][2] = '{'{0, 0}, '{0, 1}, '{1, 0}, '{0, 5}, '{5, 0}, '{0, 20}, '{20, 0}, '{3, 3}};
    int policies[] = '{-2, 0, 1, 5, 20};

    // Fixed seed, so every run (and the TAs' run) sees the same traffic.
    process::self().srandom(427);
    $display("PIT stress test");
    repeat (20) @(posedge clk);
    resetn <= 1'b1;
    repeat (5) @(posedge clk);

    //-----------------------------------------------------------------------
    begin_test("1. Reset values (control = 3, delay-value = 1,666,667)");
    check_read(ADDR_CTRL, "after reset");
    check_read(ADDR_DELAY, "after reset");
    end_test();

    //-----------------------------------------------------------------------
    begin_test("2. Register read/write");
    foreach (ctrl_vals[i]) begin
      reg_write(ADDR_CTRL, ctrl_vals[i]);
      check_read(ADDR_CTRL, "control write then read");
    end
    foreach (delay_vals[i]) begin
      reg_write(ADDR_DELAY, delay_vals[i]);
      check_read(ADDR_DELAY, "delay-value write then read");
      check_read(ADDR_CTRL, "control unchanged by delay-value write");
    end
    end_test();

    //-----------------------------------------------------------------------
    begin_test("3. Periodic interrupts: one-cycle irq every N cycles");
    foreach (periods[p]) begin
      int n = periods[p];
      start_timer(n);
      t_en = last_accept;
      t_prev = t_en;
      for (int k = 0; k < 6; k++) begin
        wait_irq_after(t_prev, 2 * n + 10, t, ok);
        if (!ok) begin
          error($sformatf("delay-value = %0d: no interrupt within %0d cycles of enabling (writing delay-value must reload the counter)", n, 2 * n + 10));
          break;
        end
        if (k == 0) begin
          if (int'(t - t_en) < n - GRACE || int'(t - t_en) > n + GRACE)
            error($sformatf("delay-value = %0d: first irq came %0d cycles after enabling, expected %0d",
                            n, t - t_en, n));
        end else if (t - t_prev != n) begin
          error($sformatf("delay-value = %0d: irq pulses %0d cycles apart, expected %0d",
                          n, t - t_prev, n));
        end
        t_prev = t;
      end
      timed_write(ADDR_CTRL, 0);
      t_dis = last_accept;
      repeat (3 * n + 10) @(posedge clk);
      if (count_irqs(t_dis + 2, cycle) != 0)
        error($sformatf("delay-value = %0d: irq after writing control = 0", n));
    end
    end_test();

    //-----------------------------------------------------------------------
    begin_test("4. Enable bit (bit 0): counter holds while disabled, then continues");
    start_timer(40);
    wait_irq_after(last_accept, 40 + 10, t0, ok);
    if (!ok) error("no interrupt with delay-value = 40");
    else begin
      int expected, actual;
      wait_until_cycle(t0 + 10);
      timed_write(ADDR_CTRL, 2);          // counter off, interrupts on
      t_dis = last_accept;
      wait_until_cycle(t_dis + 50);
      if (count_irqs(t_dis + 2, cycle) != 0)
        error("irq asserted while the enable bit was 0");
      timed_write(ADDR_CTRL, 3);
      t_en = last_accept;
      expected = 40 - int'(t_dis - t0);
      wait_irq_after(t_en, 40 + 10, t1, ok);
      if (!ok) error("no interrupt after setting the enable bit again");
      else begin
        actual = int'(t1 - t_en);
        if (actual < expected - GRACE || actual > expected + GRACE)
          error($sformatf({"after re-enabling, the next irq came %0d cycles later; expected about %0d ",
                           "(the counter should hold while disabled and continue from where it stopped)"},
                          actual, expected));
        expect_period(t1, 40, "period after re-enabling", t);
      end
    end
    end_test();

    //-----------------------------------------------------------------------
    begin_test("5. Interrupt enable bit (bit 1): counter keeps running, irq stays low");
    start_timer(10);
    wait_irq_after(last_accept, 10 + 10, t0, ok);
    if (!ok) error("no interrupt with delay-value = 10");
    else begin
      repeat (3) @(posedge clk);
      timed_write(ADDR_CTRL, 1);          // counter on, interrupts off
      t_dis = last_accept;
      wait_until_cycle(t_dis + 55);
      if (count_irqs(t_dis + 2, cycle) != 0)
        error("irq asserted while the interrupt enable bit was 0");
      reg_write(ADDR_CTRL, 3, 0, 0, -1);
      t_en = last_accept;
      wait_irq_after(t_en, 10 + 10, t1, ok);
      if (!ok) error("no interrupt after setting the interrupt enable bit again");
      else begin
        if ((t1 - t0) % 10 != 0)
          error($sformatf({"irq phase shifted by %0d cycles while interrupts were disabled ",
                           "(the counter should keep counting and reloading when only bit 1 is cleared)"},
                          (t1 - t0) % 10));
        expect_period(t1, 10, "period after re-enabling interrupts", t);
      end
    end
    end_test();

    //-----------------------------------------------------------------------
    begin_test("6. Writing delay-value while running reloads the counter");
    start_timer(10);
    wait_irq_after(last_accept, 10 + 10, t0, ok);
    if (!ok) error("no interrupt with delay-value = 10");
    else begin
      repeat (2) @(posedge clk);
      reg_write(ADDR_DELAY, 25, 0, 0, -1);
      t_en = last_accept;
      wait_irq_after(t_en, 25 + 10, t1, ok);
      if (!ok) error("no interrupt after changing delay-value to 25");
      else begin
        if (int'(t1 - t_en) < 25 - GRACE || int'(t1 - t_en) > 25 + GRACE)
          error($sformatf({"after writing delay-value = 25 mid-count, the next irq came %0d cycles later; ",
                           "expected 25 (writing delay-value must reload the counter)"}, t1 - t_en));
        expect_period(t1, 25, "period after changing delay-value", t);
        expect_period(t, 25, "period after changing delay-value", t_prev);
      end
    end
    end_test();

    //-----------------------------------------------------------------------
    begin_test("7. No irq after disabling, at every point in the count (delay-value = 3)");
    repeat (40) begin
      logic [31:0] v = $urandom_range(0, 2);
      start_timer(3);
      repeat ($urandom_range(0, 6)) @(posedge clk);
      timed_write(ADDR_CTRL, v);
      t_dis = last_accept;
      repeat (12) @(posedge clk);
      if (count_irqs(t_dis + 2, cycle) != 0)
        error($sformatf("irq asserted after writing control = %0d", v));
    end
    end_test();

    //-----------------------------------------------------------------------
    begin_test("8. AW/W ordering: W before AW, AW before W, long gaps");
    reg_write(ADDR_CTRL, 0);
    foreach (gaps[g]) begin
      logic [31:0] v;
      v = 32'd1000 + $urandom_range(0, 100000);
      reg_write(ADDR_DELAY, v, gaps[g][0], gaps[g][1]);
      check_read(ADDR_DELAY, $sformatf("AWVALID delay %0d, WVALID delay %0d", gaps[g][0], gaps[g][1]));
      check_read(ADDR_CTRL, "control unchanged by delay-value write");
      reg_write(ADDR_CTRL, (g % 2) ? 2 : 0, gaps[g][0], gaps[g][1]);
      check_read(ADDR_CTRL, $sformatf("AWVALID delay %0d, WVALID delay %0d", gaps[g][0], gaps[g][1]));
      check_read(ADDR_DELAY, "delay-value unchanged by control write");
    end
    end_test();

    //-----------------------------------------------------------------------
    begin_test("9. BREADY/RREADY back-pressure (ready before valid, and late ready)");
    reg_write(ADDR_CTRL, 0);
    foreach (policies[p]) begin
      reg_write(ADDR_DELAY, 32'd2000 + p, -1, -1, policies[p]);
      check_read(ADDR_DELAY, $sformatf("BREADY policy %0d", policies[p]), -1, policies[p]);
      check_read(ADDR_CTRL, $sformatf("RREADY policy %0d", policies[p]), -1, policies[p]);
    end
    end_test();

    //-----------------------------------------------------------------------
    begin_test("10. Back-to-back transactions with no idle cycles");
    repeat (40) begin
      logic [3:0] a = $urandom_range(0, 1) ? ADDR_DELAY : ADDR_CTRL;
      logic [31:0] v = (a == ADDR_CTRL) ? $urandom_range(0, 3) : 32'd100 + $urandom_range(0, 5000);
      reg_write(a, v, 0, 0, -2);
      check_read(a, "back-to-back write then read", 0, -2);
      check_read(a ^ 4'h4, "back-to-back read of the other register", 0, -2);
    end
    end_test();

    //-----------------------------------------------------------------------
    begin_test("11. Concurrent read and write");
    repeat (60) begin
      logic [3:0] wa = $urandom_range(0, 1) ? ADDR_DELAY : ADDR_CTRL;
      logic [3:0] ra = $urandom_range(0, 1) ? ADDR_DELAY : ADDR_CTRL;
      logic [31:0] v = (wa == ADDR_CTRL) ? $urandom_range(0, 3) : 32'd100 + $urandom_range(0, 5000);
      logic [31:0] old = model(ra);
      logic [31:0] got;
      fork
        axi_write(wa, v);
        axi_read(ra, got);
      join
      if (wa == ADDR_CTRL) model_ctrl = v; else model_delay = v;
      if (ra != wa) begin
        if (!value_ok(ra, got, old))
          error($sformatf("read of %s during a write to %s returned %0d, expected %0d",
                          regname(ra), regname(wa), got, old));
      end else if (!value_ok(ra, got, old) && !value_ok(ra, got, v)) begin
        error($sformatf("read of %s during a write to it returned %0d, expected old (%0d) or new (%0d) value",
                        regname(ra), got, old, v));
      end
      check_read(wa, "write issued concurrently with a read");
    end
    end_test();

    //-----------------------------------------------------------------------
    begin_test("12. Random traffic");
    repeat (1000) begin
      int op = $urandom_range(0, 2);
      logic [3:0] a = $urandom_range(0, 1) ? ADDR_DELAY : ADDR_CTRL;
      logic [31:0] v = (a == ADDR_CTRL) ? $urandom_range(0, 3)
                     : ($urandom_range(0, 3) == 0 ? $urandom : 32'd2 + $urandom_range(0, 200));
      case (op)
        0: reg_write(a, v);
        1: check_read(a, "random read");
        2: begin
          logic [31:0] got;
          logic [31:0] old = model(a ^ 4'h4);
          fork
            reg_write(a, v);
            axi_read(a ^ 4'h4, got);
          join
          if (!value_ok(a ^ 4'h4, got, old))
            error($sformatf("read of %s during a write to %s returned %0d, expected %0d",
                            regname(a ^ 4'h4), regname(a), got, old));
        end
      endcase
      repeat ($urandom_range(0, 2)) @(posedge clk);
    end
    check_read(ADDR_CTRL, "final");
    check_read(ADDR_DELAY, "final");
    end_test();

    finish_sim();
  endtask

endmodule

`default_nettype wire
