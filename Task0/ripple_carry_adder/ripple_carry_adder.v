// Verilog code for 2 bit ripple_carry_adder
// Define module
module ripple_carry_adder (
    input [1:0] a, b,
    input cin, // Define all input ports
    output [1:0] sum,
    output c_out // Define all output ports
);
wire c1; // Define intermediate carry as c1

full_adder FA0 (a[0], b[0], cin, sum[0], c1); // instantiate full_adder (FA0)
full_adder FA1 (a[1], b[1], c1, sum[1], c_out); // instantiate full_adder (FA1)

endmodule
