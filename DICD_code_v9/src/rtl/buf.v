`include "include/data_type.svh"

// 循環 buffer，保存最近 256 個角度
module buf (
    input  logic        clk,
    input  logic        rst,       // active-high reset
    input  ang_t        ang_in,
    output ang_t  angle_buf[0:255], // expose buffer給 select_eps
    output logic [7:0] write_ptr  // expose寫指標給 select_eps
);

    logic [7:0] ptr;

    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            ptr <= 8'd0;
        end else begin
            ptr <= ptr + 1;
        end
    end

    // 寫入 buffer
    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            integer i;
            for (i=0; i<256; i=i+1)
                angle_buf[i] <= '0;
        end else begin
            angle_buf[ptr] <= ang_in;
        end
    end

    assign write_ptr = ptr;

endmodule
