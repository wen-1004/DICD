`include "include/data_type.svh"
// typedef logic signed [15:0] gamma_t;
// typedef logic signed [12:0] ang_t;

module angle (
    input  logic    clk,
    input  logic    rst,             
    input  gamma_t  gamma_in_real,   // x
    input  gamma_t  gamma_in_imag,   // y
    output ang_t    ang_out          // atan2(y,x) with 8-cycle delay
);

    // ------------------------------------------------------------
    // CORDIC 參數
    // ------------------------------------------------------------
    localparam int ITERS   = 8;     // cordic iterations
    localparam int F_ANG   = 10;    // ang_t 小數位
    localparam int DLY     = 8;     // <<<=== 延遲 8 cycles

    // π/2 ≈ 1.5708 → ×1024 ≈ 1608
    localparam ang_t HALF_PI     = ang_t'(13'sd1608);
    localparam ang_t NEG_HALF_PI = ang_t'(-13'sd1608);

    // atan(2^-i) table (Q2.10)
    localparam ang_t ATAN_LUT[0:ITERS-1] = '{
        ang_t'(13'sd804),
        ang_t'(13'sd475),
        ang_t'(13'sd251),
        ang_t'(13'sd127),
        ang_t'(13'sd64),
        ang_t'(13'sd32),
        ang_t'(13'sd16),
        ang_t'(13'sd8)
    };

    // ------------------------------------------------------------
    // 中間訊號 (comb)
    // ------------------------------------------------------------
    gamma_t x0, y0;
    gamma_t x_q, y_q;
    ang_t   z_q;

    gamma_t x_iter[0:ITERS];
    gamma_t y_iter[0:ITERS];
    ang_t   z_iter[0:ITERS];

    ang_t   ang_now;      // 本拍完成的 CORDIC 輸出

    // ------------------------------------------------------------
    // 組合邏輯：CORDIC atan2 (same as SystemC)
    // ------------------------------------------------------------
    always_comb begin
        // 原始輸入
        x0 = gamma_in_real;   
        y0 = gamma_in_imag;   
        x_q = x0;
        y_q = y0;
        z_q = '0;

        // Quadrant 修正
        if (x0 < 0) begin
            if (y0 >= 0) begin
                x_q =  y0;
                y_q = -x0;
                z_q =  HALF_PI;
            end else begin
                x_q = -y0;
                y_q =  x0;
                z_q =  NEG_HALF_PI;
            end
        end

        // CORDIC 初始
        x_iter[0] = x_q;
        y_iter[0] = y_q;
        z_iter[0] = z_q;

        // CORDIC 迭代 (8 stages)
        for (int i = 0; i < ITERS; i++) begin
            logic signed [15:0] x_shift = x_iter[i] >>> i;
            logic signed [15:0] y_shift = y_iter[i] >>> i;

            if (y_iter[i] >= 0) begin
                x_iter[i+1] = x_iter[i] + y_shift;
                y_iter[i+1] = y_iter[i] - x_shift;
                z_iter[i+1] = z_iter[i] + ATAN_LUT[i];
            end else begin
                x_iter[i+1] = x_iter[i] - y_shift;
                y_iter[i+1] = y_iter[i] + x_shift;
                z_iter[i+1] = z_iter[i] - ATAN_LUT[i];
            end
        end

        ang_now = z_iter[ITERS];   // final angle
    end

    // ------------------------------------------------------------
    // Delay line (8-cycle FIFO) —— 對應 SystemC 的 delay_line[]
    // ------------------------------------------------------------
    ang_t dly_reg[0:DLY-1];

    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            for (int i = 0; i < DLY; i++)
                dly_reg[i] <= '0;
            ang_out <= '0;

        end else begin
            // pipeline shift (右邊輸出，左邊輸入)
            // dly_reg[7] ← dly_reg[6] ← ... ← dly_reg[0] ← ang_now
            for (int i = DLY-1; i > 0; i--)
                dly_reg[i] <= dly_reg[i-1];

            dly_reg[0] <= ang_now;

            // 輸出最尾端的 (8-cycle 出來)
            ang_out <= dly_reg[DLY-1];
        end
    end

endmodule