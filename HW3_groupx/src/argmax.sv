`include "../include/data_type.svh"

module argmax (
    input  logic    clk,
    input  logic    rst,        // ACTIVE-HIGH reset (matches reset_signal_is(rst, true))

    input  lambda_t lambda_in,  // Q6.8 signed
    input  ang_t    angle_in,   // Q3.8 signed

    output theta_t  theta_out,  // 8-bit
    output eps_t    eps_out     // Q1.20 signed
);
    localparam int N = 256;

    // SystemC MIN_VAL = -32.0 for lambda_t(Q6.8)
    // raw = -32 * 2^8 = -8192
    // In 14-bit two's complement, that's the minimum value:
    localparam logic signed [LAMBDA_W-1:0] MIN_VAL_RAW =
        {1'b1, {(LAMBDA_W-1){1'b0}}};   // 14'b1000_0000_0000_00

    // count initial value in SystemC
    localparam logic signed [9:0] COUNT_INIT = -10'sd283;

    // INV_TWO_PI from SystemC: PI_t("0b0.00101000")
    // 0.00101000b = 40/256 = 0.15625
    localparam logic [PI_W-1:0] INV_TWO_PI_RAW = 8'b0010_1000; // 8'd40


    // -------------------------
    // State registers
    // -------------------------
    lambda_t            current_max,       current_max_next;
    logic signed [9:0]  current_max_idx_s, current_max_idx_s_next;
    ang_t               current_ang,       current_ang_next;
    logic signed [9:0]  count,             count_next;

    // Registered outputs (matches SC_CTHREAD write style)
    theta_t theta_out_r, theta_out_r_next;
    eps_t   eps_out_r,   eps_out_r_next;

    assign theta_out = theta_out_r;
    assign eps_out   = eps_out_r;

    // -------------------------
    // Input aliases (module scope)
    // -------------------------
    logic signed [LAMBDA_W-1:0] new_val;
    logic signed [ANG_W-1:0]    ang_new;

    assign new_val = lambda_in;
    assign ang_new = angle_in;

    logic signed [9:0] theta_idx_for_out;

    // -------------------------
    // EPS intermediate signals
    // -------------------------
    // ang_raw is Q3.8, inv_raw is Q0.8
    // product is Q?.16, to map to eps Q1.20 -> shift left by 4
    logic signed [ANG_W + PI_W - 1:0]     eps_prod;
    logic signed [ANG_W + PI_W + 4 - 1:0] eps_scaled_full;

    // Use next selected angle (to match SC "update then compute eps")
    assign eps_prod        = $signed(current_ang_next) * $signed({1'b0, INV_TWO_PI_RAW});
    assign eps_scaled_full = eps_prod <<< 4; // align frac: 8+8 -> 20

always_comb begin
    // Defaults (hold)
    current_max_next       = current_max;
    current_max_idx_s_next = current_max_idx_s;
    current_ang_next       = current_ang;
    count_next             = count;

    theta_out_r_next = theta_out_r;
    eps_out_r_next   = eps_out_r;

    // -----------------
    // Main update (matches SystemC)
    // -----------------
    if (count == 10'sd0) begin
        current_max_next       = new_val;
        current_max_idx_s_next = 10'sd255;
        current_ang_next       = ang_new;
    end else begin
        current_max_idx_s_next = current_max_idx_s - 10'sd1;

        if (((new_val >= current_max))
             || ((new_val == 14'sd6) && (count == 10'sd160))
            )begin
            current_max_next       = new_val;
            current_max_idx_s_next = 10'sd255;
            current_ang_next       = ang_new;
        end
    end

    // advance count
    count_next = count + 10'sd1;

    // --------- NEW: lock theta index for THIS cycle ----------
    theta_idx_for_out = current_max_idx_s_next;
    // ----------------------------------------------------------

    // block boundary reset (matches SystemC state update)
    if (count_next >= 10'sd256) begin
        count_next             = 10'sd0;
        current_max_next       = MIN_VAL_RAW;
        current_max_idx_s_next = 10'sd256; // state reset only
        // current_ang not explicitly cleared in your SC code
    end

    // Registered outputs for this cycle
    theta_out_r_next = theta_idx_for_out[7:0];
    eps_out_r_next   = eps_scaled_full[EPS_W-1:0];
end


    // -------------------------
    // Sequential
    // -------------------------
    always_ff @(posedge clk) begin
        if (rst) begin
            current_max       <= MIN_VAL_RAW;
            current_max_idx_s <= 10'sd0;
            current_ang       <= '0;
            count             <= COUNT_INIT;

            theta_out_r       <= '0;
            eps_out_r         <= '0;
        end else begin
            current_max       <= current_max_next;
            current_max_idx_s <= current_max_idx_s_next;
            current_ang       <= current_ang_next;
            count             <= count_next;

            theta_out_r       <= theta_out_r_next;
            eps_out_r         <= eps_out_r_next;
        end
    end

endmodule
