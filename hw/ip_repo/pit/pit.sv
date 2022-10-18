`timescale 1 ns / 1 ps
`default_nettype none

module pit_sv #(
    // Width of S_AXI address bus
    parameter integer C_S_AXI_ADDR_WIDTH = 4
)
(
    input logic                             s_axi_aclk,
    input logic                             s_axi_aresetn,

    // AW
    input logic                             s_axi_awvalid,
    output logic                            s_axi_awready,
    input logic [C_S_AXI_ADDR_WIDTH-1:0]    s_axi_awaddr,
    input logic [2:0]                       s_axi_awprot,

    // W
    input logic                             s_axi_wvalid,
    output logic                            s_axi_wready,
    input logic [31:0]                      s_axi_wdata,
    input logic [3:0]                       s_axi_wstrb,

    // B
    output logic                            s_axi_bvalid,
    input logic                             s_axi_bready,
    output logic [1:0]                      s_axi_bresp,

    // AR
    input logic                             s_axi_arvalid,
    output logic                            s_axi_arready,
    input logic [C_S_AXI_ADDR_WIDTH-1:0]    s_axi_araddr,
    input logic [2:0]                       s_axi_arprot,

    // R
    output logic [31:0]                     s_axi_rdata,
    output logic [1:0]                      s_axi_rresp,
    output logic                            s_axi_rvalid,
    input logic                             s_axi_rready,

    output logic                            irq
);

// Add your module here

endmodule
