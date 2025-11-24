// `include "include/data_type.svh"

// module  phi_sum(
//         input		clk                         ,
//         input		rst                         ,
//         input r_t r_k_in_real            ,
//         input r_t r_k_in_imag            ,
//         input r_t r_k_minus_N_in_real    ,
//         input r_t r_k_minus_N_in_imag    ,
//         input rho_t rho                  ,
//         output phi_t phi_out 
// );

// parameter L = 16;
// integer i;

// reg phi_t delay_line [0:L-1];
// // reg signed phi_t current_sum;
// // reg signed phi_t phi_out_reg;

// reg phi_t r_k_sq;
// reg phi_t r_kmN_sq;
// reg phi_t energy_to_sum;
// reg phi_t phi_out_buf;

// assign phi_out = phi_out_buf;

// always @(*) begin                                                   // ---- cal square ----
//     r_k_sq = r_k_in_real*r_k_in_real + r_k_in_imag*r_k_in_imag; 
//     r_kmN_sq = r_k_minus_N_in_real*r_k_minus_N_in_real + r_k_minus_N_in_imag*r_k_minus_N_in_imag;
// end

// always @(*) begin                                                   // ---- *rho/2 ----
//    energy_to_sum = ((r_k_sq + r_kmN_sq) * rho) >>> 1;
// end

// always @(posedge clk or posedge rst) begin                          // ---- shift register ----
//     if (rst) begin
//         for (i = 0; i < L; i = i + 1) begin
//             delay_line[i] <= 0;
//         end
//     end
//     else begin
//         for (i = L-1; i > 0; i = i - 1) begin
//             delay_line[i] <= delay_line[i-1];
//         end
//         delay_line[0] <= energy_to_sum;
//     end
// end    

// always @(posedge clk or posedge rst) begin                          // ---- cal S[n] = S[n-1] + new - old ----
//     if (rst) begin
//         phi_out_buf <= 0;
//     end
//     else begin
//         phi_out_buf <= phi_out_buf + energy_to_sum - delay_line[L-1];
//     end
// end    

// endmodule

`include "include/data_type.svh"

module phi_sum(
        input       clk,
        input       rst,
        input r_t   r_k_in_real,
        input r_t   r_k_in_imag,
        input r_t   r_k_minus_N_in_real,
        input r_t   r_k_minus_N_in_imag,
        input rho_t rho,
        output phi_t phi_out
);

parameter L = 16;
integer i;

reg phi_t delay_line [0:L-1];
reg phi_t r_k_sq;
reg phi_t r_kmN_sq;
reg phi_t energy_to_sum;
reg phi_t phi_out_buf;

assign phi_out = phi_out_buf;

// ---------- 中間 32-bit 避免乘法 overflow ----------
reg signed [31:0] temp_rk_sq, temp_rkmN_sq;
reg signed [31:0] temp_rk_sq_shift, temp_rkmN_sq_shift;
reg signed [31:0] temp_energy;
reg signed [31:0] temp_energy_shift;

always @(*) begin
    // 計算平方，暫存 32-bit    // Q2.30
    temp_rk_sq   = r_k_in_real*r_k_in_real + r_k_in_imag*r_k_in_imag;
    temp_rkmN_sq = r_k_minus_N_in_real*r_k_minus_N_in_real + r_k_minus_N_in_imag*r_k_minus_N_in_imag;
end

always @(*) begin
    // 右移 20 位              // Q2.30->Q?.10
    temp_rk_sq_shift = temp_rk_sq >>> 20;
    temp_rkmN_sq_shift = temp_rkmN_sq >>> 20;
end

always @(*) begin
    // Q2.30->Q?.10           // 取16位回phi_t(Q6.10) 
    r_k_sq    = temp_rk_sq[15:0];
    r_kmN_sq  = temp_rkmN_sq[15:0];
end

always @(*) begin
    // energy_to_sum = ((r_k_sq + r_kmN_sq) * rho) >>> 1
    // 先用 32-bit 避免 overflow，再 shift 回 phi_t
    // (Q6.10+Q6.10)*Q1.7 shift 1bit    (Q7.17>>>1 -> Q?.16)
    temp_energy = (r_k_sq + r_kmN_sq) * rho >>> 1;
end

always @(*) begin
    //  32-bit  // Q?.16->Q?.10
    temp_energy_shift = temp_energy >>> 6;
end

always @(*) begin
    // Q?.10->Q6.10
    energy_to_sum = temp_energy_shift[0:15];
end

always @(posedge clk or posedge rst) begin
    if (rst) begin
        for (i = 0; i < L; i = i + 1)
            delay_line[i] <= 0;
    end else begin
        for (i = L-1; i > 0; i = i - 1)
            delay_line[i] <= delay_line[i-1];
        delay_line[0] <= energy_to_sum;
    end
end    

always @(posedge clk or posedge rst) begin
    if (rst)
        phi_out_buf <= 0;
    else
        phi_out_buf <= phi_out_buf + energy_to_sum - delay_line[L-1];
end    

endmodule
