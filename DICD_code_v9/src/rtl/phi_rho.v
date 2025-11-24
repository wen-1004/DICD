`include "include/data_type.svh"

// ---- 1 latency ----

module phi_rho (
    input  clk,
    input  rst,
    input  phi_t     phi_in,
    input  rho_t     rho_in,
    output phi_t     phi_rho
);

reg signed [23:0] prod_full;
logic signed [23:0] prod_shifted;
logic signed [15:0] rho_phi_q6_10;

assign prod_shifted = prod_full >>> 7;
assign rho_phi_q6_10 = prod_shifted[15:0];
assign phi_rho = rho_phi_q6_10;

always @(posedge clk or posedge rst) begin
    if (rst) begin
        prod_full <= 0;
    end
    else begin
        prod_full <= rho_in * phi_in;
    end
end

endmodule