`include "include/data_type.svh"

// 純組合電路，讀 buffer 計算 eps
module select_eps (
    input  ang_t  angle_buf[0:255],
    input  logic [7:0]    write_ptr,
    input  theta_t         theta_in,
    output eps_t           eps_out
);

    // 常數：1/(2*pi) ≈ 0.15915494309189533577
    localparam logic [19:0] INV_TWO_PI = 20'd4189;  // Q13 fixed-point

    logic [7:0] read_ptr;
    logic signed [32:0] mult_result;

    always_comb begin
        // 從 buffer 讀出對應位置
        read_ptr = (write_ptr - (8'd255 - theta_in)) & 8'hFF;
        mult_result = angle_buf[read_ptr] * INV_TWO_PI;
        eps_out = mult_result[24:4]; // 選擇固定點 slice
    end

endmodule
