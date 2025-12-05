`timescale 1ns/1ps

module i2s_transceiver #(
    parameter integer SAMPLE_BITS = 16,
    parameter integer CHANNELS    = 2,
    parameter integer CLK_DIV     = 8
)(
    input  wire                          clk,
    input  wire                          rst,

    input  wire signed [SAMPLE_BITS-1:0] tx_sample_l,
    input  wire signed [SAMPLE_BITS-1:0] tx_sample_r,
    input  wire                          tx_valid,
    output reg                           tx_ready,

    output reg  signed [SAMPLE_BITS-1:0] rx_sample_l,
    output reg  signed [SAMPLE_BITS-1:0] rx_sample_r,
    output reg                           rx_valid,
    input  wire                          rx_ready,

    output reg                           i2s_sck,
    output reg                           i2s_ws,
    input  wire                          i2s_sd_in,
    output reg                           i2s_sd_out
);

    // ---------------- Clock divider ----------------
    localparam integer DIV_W = $clog2(CLK_DIV);
    reg [DIV_W-1:0] div_cnt = {DIV_W{1'b0}};
    reg             bclk_rise;

    // Sized compare constant (Verilator-clean)
    localparam [DIV_W-1:0] DIV_MAX = CLK_DIV[DIV_W-1:0] - { {(DIV_W-1){1'b0}}, 1'b1 };

    // ---------------- I2S framing ----------------
    // Per channel: 1 dummy + SAMPLE_BITS data
    localparam integer BIT_TOTAL = SAMPLE_BITS + 1;
    localparam integer BIT_W     = $clog2(BIT_TOTAL);

    reg [BIT_W:0] bit_cnt = {BIT_W+1{1'b0}};
    reg           chan     = 1'b0;   // 0 = left, 1 = right

    // Sized compare constant (Verilator-clean)
    localparam [BIT_W:0] BIT_MAX = BIT_TOTAL[BIT_W:0] - { {BIT_W{1'b0}}, 1'b1 };

    // ---------------- Shift registers ----------------
    reg signed [SAMPLE_BITS-1:0] tx_shift;
    reg signed [SAMPLE_BITS-1:0] rx_shift;

    // ---------------- Main logic ----------------
    always @(posedge clk) begin
        if (rst) begin
            div_cnt   <= {DIV_W{1'b0}};
            i2s_sck   <= 1'b0;
            bclk_rise <= 1'b0;

            i2s_ws    <= 1'b0;
            bit_cnt   <= {BIT_W+1{1'b0}};
            chan      <= 1'b0;

            tx_ready  <= 1'b1;
            rx_valid  <= 1'b0;

            tx_shift   <= {SAMPLE_BITS{1'b0}};
            rx_shift   <= {SAMPLE_BITS{1'b0}};
            i2s_sd_out <= 1'b0;

            rx_sample_l <= {SAMPLE_BITS{1'b0}};
            rx_sample_r <= {SAMPLE_BITS{1'b0}};
        end else begin
            bclk_rise <= 1'b0;
            rx_valid  <= 1'b0;

            // -------- Bit clock --------
            if (div_cnt == DIV_MAX) begin
                div_cnt <= {DIV_W{1'b0}};
                i2s_sck <= ~i2s_sck;
                if (!i2s_sck)
                    bclk_rise <= 1'b1;
            end else begin
                div_cnt <= div_cnt + {{(DIV_W-1){1'b0}},1'b1};
            end

            // -------- Load new stereo frame --------
            if (tx_ready && tx_valid) begin
                tx_ready <= 1'b0;
                chan     <= 1'b0;
                bit_cnt  <= {BIT_W+1{1'b0}};
                i2s_ws   <= 1'b0;          // left channel
                tx_shift <= tx_sample_l;
            end

            // -------- True Philips-I2S transfer --------
            if (bclk_rise && !tx_ready) begin

                // bit 0 = dummy after WS change
                if (bit_cnt == {BIT_W+1{1'b0}}) begin
                    i2s_sd_out <= 1'b0;
                end else begin
                    i2s_sd_out <= tx_shift[SAMPLE_BITS-1];
                    tx_shift   <= {tx_shift[SAMPLE_BITS-2:0], 1'b0};
                    rx_shift   <= {rx_shift[SAMPLE_BITS-2:0], i2s_sd_in};
                end

                // End of one channel word
                if (bit_cnt == BIT_MAX) begin
                    bit_cnt <= {BIT_W+1{1'b0}};

                    if (!chan) begin
                        // finished LEFT
                        rx_sample_l <= rx_shift;
                        chan        <= 1'b1;
                        i2s_ws      <= 1'b1;          // switch to right
                        tx_shift    <= tx_sample_r;
                    end else begin
                        // finished RIGHT
                        rx_sample_r <= rx_shift;
                        tx_ready    <= 1'b1;
                        if (rx_ready)
                            rx_valid <= 1'b1;
                    end
                end else begin
                    bit_cnt <= bit_cnt + {{BIT_W{1'b0}},1'b1};
                end
            end
        end
    end

endmodule
