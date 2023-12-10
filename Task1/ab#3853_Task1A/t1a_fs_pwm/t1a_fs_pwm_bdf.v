// Copyright (C) 2020  Intel Corporation. All rights reserved.
// Your use of Intel Corporation's design tools, logic functions 
// and other software and tools, and any partner logic 
// functions, and any output files from any of the foregoing 
// (including device programming or simulation files), and any 
// associated documentation or information are expressly subject 
// to the terms and conditions of the Intel Program License 
// Subscription Agreement, the Intel Quartus Prime License Agreement,
// the Intel FPGA IP License Agreement, or other applicable license
// agreement, including, without limitation, that your use is for
// the sole purpose of programming logic devices manufactured by
// Intel and sold by Intel or its authorized distributors.  Please
// refer to the applicable agreement for further details, at
// https://fpgasoftware.intel.com/eula.

// PROGRAM		"Quartus Prime"
// VERSION		"Version 20.1.0 Build 711 06/05/2020 SJ Lite Edition"
// CREATED		"Sun Oct 15 21:10:22 2023"

module t1a_fs_pwm_bdf(
	clk_50M,
	duty_cycle,
	pwm_signal,
	clk_195KHz,
	clk_3125KHz
);


input wire	clk_50M;
input wire	[3:0] duty_cycle;
output wire	pwm_signal;
output wire	clk_195KHz;
output wire	clk_3125KHz;

wire	SYNTHESIZED_WIRE_0;

assign	clk_3125KHz = SYNTHESIZED_WIRE_0;




frequency_scaling	b2v_inst(
	.clk_50M(clk_50M),
	.clk_3125KHz(SYNTHESIZED_WIRE_0));


pwm_generator	b2v_inst1(
	.clk_3125KHz(SYNTHESIZED_WIRE_0),
	.duty_cycle(duty_cycle),
	.clk_195KHz(clk_195KHz),
	.pwm_signal(pwm_signal));


endmodule
