`include "../include/data_type.svh"

module minus (
    input  logic   clk,
    input  logic   rst,  
    input  mag_t   mag_in,
    input  phi_t   phi_in,
    input  rho_t   rho_in,
    output lambda_t lambda_out
);

    // rho  : Q1.7  (RHO_W signed)
    // phi  : Q6.8  (PHI_W unsigned)
    // mag  : Q6.8  (MAG_W signed)
    //
    // prod_full  width = RHO_W + PHI_W
    // frac bits  = RHO_FRAC + PHI_FRAC
    // shift by RHO_FRAC to go back to Q6.8 domain

    localparam rho_t rho_const = 8'sb01011111; // 0.9921875 in Q1.7

    // =========================================================
    // Stage 1: multiply (largest cut)
    // =========================================================
    logic signed [RHO_W + PHI_W - 1:0] prod_full_w;

    // Cast phi to signed positive before multiply
    assign prod_full_w = $signed(rho_const) * $signed({1'b0, phi_in});

    logic signed [RHO_W + PHI_W - 1:0] prod_full_s1;
    mag_t                              mag_s1;

    always_ff @(posedge clk) begin
        if (rst) begin
            prod_full_s1 <= '0;
            mag_s1       <= '0;
        end else begin
            prod_full_s1 <= prod_full_w;
            mag_s1       <= mag_in;      // align with product pipeline
        end
    end

    // =========================================================
    // Stage 2: shift + truncate to 14-bit Q6.8
    // =========================================================
    logic signed [RHO_W + PHI_W - 1:0] prod_shifted_w;
    logic signed [LAMBDA_W-1:0]        rho_phi_q6_8_w;

    assign prod_shifted_w = prod_full_s1 >>> RHO_FRAC;
    assign rho_phi_q6_8_w = prod_shifted_w[LAMBDA_W-1:0];

    logic signed [LAMBDA_W-1:0] rho_phi_q6_8_s2;
    mag_t                       mag_s2;

    always_ff @(posedge clk) begin
        if (rst) begin
            rho_phi_q6_8_s2 <= '0;
            mag_s2          <= '0;
        end else begin
            rho_phi_q6_8_s2 <= rho_phi_q6_8_w;
            mag_s2          <= mag_s1;   // keep alignment
        end
    end

    // =========================================================
    // Stage 3: subtract and register output
    // =========================================================
    logic signed [LAMBDA_W-1:0] lambda_calc_w;

    assign lambda_calc_w = $signed(mag_s2) - $signed(rho_phi_q6_8_s2);

    always_ff @(posedge clk) begin
        if (rst) begin
            lambda_out <= '0;
        end else begin
            lambda_out <= lambda_t'(lambda_calc_w);
        end
    end

endmodule
