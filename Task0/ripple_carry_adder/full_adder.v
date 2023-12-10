// Verilog code for Full Adder
// Define Full Adder module
module full_adder (
    input a, b, c_in, // Define input ports a, b and c_in
    output sum , c_out // Define output ports sum and c_out
);

assign sum = a ^ b ^ c_in; // Define Sum logic
assign c_out = ((a & b) | (c_in & (a ^ b))); // Define Carry_out logic

endmodule
