`include "../include/data_type.svh"

module minus (
    input  logic    clk,
    input  logic    rst,  

    input  mag_t    mag_in,
    input  phi_t    phi_in,
    input  rho_t    rho_in,     // kept for interface compatibility (unused)

    output lambda_t lambda_out
);
    import data_type::*;

    // ------------------------------------------------------------
    // 2-stage pipelined minus with fixed rho constant
    //
    // rho  : Q1.7  (8 bits signed)
    // phi  : Q6.8  (14 bits unsigned)
    // mag  : Q6.8  (14 bits signed)
    //
    // S1: prod_full = rho_const * phi_in   (register)
    //     mag_in aligned into mag_s1
    // S2: (prod_full >>> RHO_FRAC)[13:0] then mag - rho*phi (register)
    //
    // Total latency: 2 cycles
    // ------------------------------------------------------------

    // 0.9921875 in Q1.7
    localparam rho_t RHO_CONST = 8'sb01111111;

    // -------------------------
    // Stage 1: multiply + align mag
    // -------------------------
    logic signed [RHO_W + PHI_W - 1:0] prod_full_w;
    logic signed [RHO_W + PHI_W - 1:0] prod_full_s1;
    mag_t                              mag_s1;

    // Cast phi to signed positive before multiply
    assign prod_full_w = $signed(RHO_CONST) * $signed({1'b0, phi_in});

    always_ff @(posedge clk) begin
        if (rst) begin
            prod_full_s1 <= '0;
            mag_s1       <= '0;
        end else begin
            prod_full_s1 <= prod_full_w;
            mag_s1       <= mag_in;
        end
    end

    // -------------------------
    // Stage 2: shift + truncate + subtract
    // -------------------------
    logic signed [RHO_W + PHI_W - 1:0] prod_shifted_s1;
    logic signed [LAMBDA_W-1:0]        rho_phi_q6_8_s1;
    logic signed [LAMBDA_W-1:0]        lambda_calc_w;

    assign prod_shifted_s1 = prod_full_s1 >>> RHO_FRAC;
    assign rho_phi_q6_8_s1 = prod_shifted_s1[LAMBDA_W-1:0];

    assign lambda_calc_w   = $signed(mag_s1) - $signed(rho_phi_q6_8_s1);

    always_ff @(posedge clk) begin
        if (rst) begin
            lambda_out <= '0;
        end else begin
            lambda_out <= lambda_t'(lambda_calc_w);
        end
    end

endmodule
