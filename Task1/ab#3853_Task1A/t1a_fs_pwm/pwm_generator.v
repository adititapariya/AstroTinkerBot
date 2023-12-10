// AstroTinker Bot : Task 1A : PWM Generator
/*
Instructions
-------------------
Students are not allowed to make any changes in the Module declaration.
This file is used to design a module which will scale down the 3.125MHz Clock Frequency to 195.125KHz and perform Pulse Width Modulation on it.

Recommended Quartus Version : 20.1
The submitted project file must be 20.1 compatible as the evaluation will be done on Quartus Prime Lite 20.1.

Warning: The error due to compatibility will not be entertained.
-------------------
*/

//PWM Generator
//Inputs : clk_3125KHz, duty_cycle
//Output : clk_195KHz, pwm_signal
module pwm_generator(
    input clk_3125KHz,
    input [3:0] duty_cycle,
    output reg clk_195KHz, pwm_signal
);

reg [3:0] count=0;
reg [2:0] counter = 0;
reg pwm_output;

initial begin
    clk_195KHz = 0; pwm_signal = 1'b1;
end

//////////////////DO NOT MAKE ANY CHANGES ABOVE THIS LINE//////////////////

/*
Add your logic here
*/



always @ (posedge clk_3125KHz) begin
    if (!counter) clk_195KHz = ~clk_195KHz; // Toggles the clock signal when counter reaches 15
	counter = counter + 1'b1; // Increment counter
end
always @(posedge clk_3125KHz) begin
    if (count == 4'd0) begin
        pwm_output = 1'b1;
    end else if (count < duty_cycle) begin
        pwm_output = 1'b1;
    end else begin
        pwm_output = 1'b0;
    end

    if (count == 4'd15) begin
        count = 4'd0;
    end else begin
        count = count + 1;
    end
end

always @(posedge clk_3125KHz) begin
    pwm_signal = pwm_output; 
end
//////////////////DO NOT MAKE ANY CHANGES BELOW THIS LINE//////////////////

endmodule