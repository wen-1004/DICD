`include "include/data_type.svh"

module delay_n (
        input		clk                 ,
        input		rst                 ,
        input r_t rx_re_in       ,
        input r_t rx_img_in      ,
        output r_t r_real    ,
        output r_t r_imag    ,
        output r_t r_dN_real , 
        output r_t r_dN_imag 
);

parameter N = 256;

reg r_t delay_line_real [0:N-1];
reg r_t delay_line_imag [0:N-1];
// reg signed r_t prev_real;
// reg signed r_t prev_imag;
// reg [15:0] count;
reg r_t r_real_buf;
reg r_t r_imag_buf;
reg r_t r_dN_real_buf;
reg r_t r_dN_imag_buf;

assign r_real = r_real_buf;
assign r_imag = r_imag_buf;
assign r_dN_real = r_dN_real_buf;
assign r_dN_imag = r_dN_imag_buf;

integer i;

always @(posedge clk or posedge rst) begin          // ---- 透傳 rx_re/img_in ----      // ---- 輸出 r_dN_real/img ----
    if (rst) begin
        r_dN_real_buf <= 0;
        r_dN_imag_ <= 0;
        r_real <= 0;
        r_imag <= 0;
    end
    else begin
        r_real_buf <= rx_re_in;
        r_imag_buf <= rx_img_in;
        r_dN_real_buf <= delay_line_real[N-1];
        r_dN_imag_buf <= delay_line_imag[N-1];
    end
end

always @(posedge clk or posedge rst) begin          // ---- shift register ----
    if (rst) begin
        for (i = 0; i < N; i = i + 1) begin
            delay_line_real[i] <= 0;
            delay_line_imag[i] <= 0;
        end
    end
    else begin
        for (i = N-1; i > 0; i = i - 1) begin
            delay_line_real[i] <= delay_line_real[i-1];
            delay_line_imag[i] <= delay_line_imag[i-1];
        end
        delay_line_real[0] <= rx_re_in;
        delay_line_imag[0] <= rx_img_in;
    end
end

// always @(posedge clk or posedge rst) begin
//     if (rst)
//         count <= 0;
//     else 
//         count <= count + 1;
// end

endmodule
