
`timescale 1 ns / 1 ps

module pit #(
    // Width of S_AXI address bus
    parameter integer C_S_AXI_ADDR_WIDTH = 4
)
(
    input wire                              s_axi_aclk,
    input wire                              s_axi_aresetn,

    // AW
    input wire                              s_axi_awvalid,
    output wire                             s_axi_awready,
    input wire [C_S_AXI_ADDR_WIDTH-1:0]     s_axi_awaddr,
    input wire [2:0]                        s_axi_awprot,

    // W
    input wire                              s_axi_wvalid,
    output wire                             s_axi_wready,
    input wire [31:0]                       s_axi_wdata,
    input wire [3:0]                        s_axi_wstrb,

    // B
    output wire                             s_axi_bvalid,
    input wire                              s_axi_bready,
    output wire [1:0]                       s_axi_bresp,

    // AR
    input wire                              s_axi_arvalid,
    output wire                             s_axi_arready,
    input wire [C_S_AXI_ADDR_WIDTH-1:0]     s_axi_araddr,
    input wire [2:0]                        s_axi_arprot,

    // R
    output wire [31:0]                      s_axi_rdata,
    output wire [1:0]                       s_axi_rresp,
    output wire                             s_axi_rvalid,
    input wire                              s_axi_rready,

    output wire                             irq
);

// Instantiation of Axi Bus Interface s_axi
	pit_sv 
        #(.C_S_AXI_ADDR_WIDTH(C_S_AXI_ADDR_WIDTH))
    pit_sv_inst (    
    .s_axi_aclk(s_axi_aclk),
    .s_axi_aresetn(s_axi_aresetn),
    
    .s_axi_awvalid(s_axi_awvalid),
    .s_axi_awready(s_axi_awready),
    .s_axi_awaddr(s_axi_awaddr),
    .s_axi_awprot(s_axi_awprot),
    
    .s_axi_wvalid(s_axi_wvalid),
    .s_axi_wready(s_axi_wready),
    .s_axi_wdata(s_axi_wdata),
    .s_axi_wstrb(s_axi_wstrb),

    .s_axi_bvalid(s_axi_bvalid),
    .s_axi_bready(s_axi_bready),
    .s_axi_bresp(s_axi_bresp),

    .s_axi_arvalid(s_axi_arvalid),
    .s_axi_arready(s_axi_arready),
    .s_axi_araddr(s_axi_araddr),
    .s_axi_arprot(s_axi_arprot),

    .s_axi_rdata(s_axi_rdata),
    .s_axi_rresp(s_axi_rresp),
    .s_axi_rvalid(s_axi_rvalid),
    .s_axi_rready(s_axi_rready),

    .irq(irq)
	);

endmodule
