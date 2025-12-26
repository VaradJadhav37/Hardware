`timescale 1ns / 1ps

module ram(
    input  [7:0] addr,
    input        clk,
    output [7:0] out
);

    reg [7:0] data [0:255];

    assign out = data[addr];

    integer i;

    initial begin
        data[0] = 8'h00;
        data[1] = 8'h02;
        data[2] = 8'h08;
        data[3] = 8'h09;
        data[4] = 8'h0A;
    end

endmodule
