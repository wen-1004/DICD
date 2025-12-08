`include "include/data_type.svh"

module minus (
    input  logic clk,
    input  logic rst,  
    input  mag_t     mag_in,
    input  phi_t     phi_in,
    input  rho_t     rho_in,
    output lambda_t  lambda_out
);
    import data_type::*;
    localparam int N_DELAY = 6;

    // rho  : Q1.7  (8 bits signed)
    // phi  : Q6.8  (14 bits unsigned)
    // mag  : Q6.8  (14 bits signed)
    //
    // prod_full  width = RHO_W + PHI_W = 22
    // fractional = RHO_FRAC + PHI_FRAC = 7 + 8 = 15  => Q?.15
    // shift right by 7 to return to 8 fractional bits

    logic signed [RHO_W + PHI_W - 1:0] prod_full;     // 22-bit
    logic signed [RHO_W + PHI_W - 1:0] prod_shifted;  // 22-bit
    logic signed [LAMBDA_W-1:0]        rho_phi_q6_8;  // 14-bit wrapped
    logic signed [LAMBDA_W-1:0]        lambda_calc;

    // Cast phi to signed positive before multiply
    assign prod_full    = $signed(rho_in) * $signed({1'b0, phi_in});

    assign prod_shifted = prod_full >>> RHO_FRAC;

    assign rho_phi_q6_8 = prod_shifted[LAMBDA_W-1:0];

    // 14-bit subtract (consistent widths)
    assign lambda_calc  = $signed(mag_in) - $signed(rho_phi_q6_8);

    // 5-cycle delay line
    lambda_t delay_line [N_DELAY];

    always_ff @(posedge clk) begin
        if (rst) begin
            for (int i = 0; i < N_DELAY; i++) begin
                delay_line[i] <= '0;
            end
        end else begin
            delay_line[0] <= lambda_calc;
            for (int i = 1; i < N_DELAY; i++) begin
                delay_line[i] <= delay_line[i-1];
            end
        end
    end

    assign lambda_out = delay_line[N_DELAY-1];

endmodule
