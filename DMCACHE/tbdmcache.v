`timescale 1ns / 1ps

module tb_dmcache;

    reg clk;
    reg [7:0] addr;
    wire hit;
    wire [7:0] out;

    dmcache dut (
        .addr(addr),
        .clk(clk),
        .hit(hit),
        .out(out)
    );

    // Clock generation
    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end

    // Address stimulus
    initial begin
        addr = 8'd0; #10;
        addr = 8'd1; #10;
        addr = 8'd2; #10;
        addr = 8'd3; #10;
        addr = 8'd4; #10;

        addr = 8'd0; #10;
        addr = 8'd1; #10;

        #50 $finish;
    end

endmodule
