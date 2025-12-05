// top.v
// Top-level for Verilator: loopback i2s_sd_out to i2s_sd_in.

`timescale 1ns/1ps

module top (
    input  wire         clk,
    input  wire         rst,

    // Parallel side for testbench
    input  wire signed [15:0] tb_tx_sample_l,
    input  wire signed [15:0] tb_tx_sample_r,
    input  wire                tb_tx_valid,
    output wire                tb_tx_ready,

    output wire signed [15:0] tb_rx_sample_l,
    output wire signed [15:0] tb_rx_sample_r,
    output wire                tb_rx_valid,
    input  wire                tb_rx_ready
);

    wire i2s_sck;
    wire i2s_ws;
    wire i2s_sd_out;
    wire i2s_sd_in;

    // Loopback: send output back to input
    assign i2s_sd_in = i2s_sd_out;

    i2s_transceiver #(
        .SAMPLE_BITS (16),
        .CHANNELS    (2),
        .CLK_DIV     (8)    // adjust for your clk
    ) i2s0 (
        .clk         (clk),
        .rst         (rst),

        .tx_sample_l (tb_tx_sample_l),
        .tx_sample_r (tb_tx_sample_r),
        .tx_valid    (tb_tx_valid),
        .tx_ready    (tb_tx_ready),

        .rx_sample_l (tb_rx_sample_l),
        .rx_sample_r (tb_rx_sample_r),
        .rx_valid    (tb_rx_valid),
        .rx_ready    (tb_rx_ready),

        .i2s_sck     (i2s_sck),
        .i2s_ws      (i2s_ws),
        .i2s_sd_in   (i2s_sd_in),
        .i2s_sd_out  (i2s_sd_out)
    );

endmodule
