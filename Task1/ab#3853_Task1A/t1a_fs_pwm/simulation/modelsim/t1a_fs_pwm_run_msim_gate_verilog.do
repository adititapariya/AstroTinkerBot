transcript on
if {[file exists gate_work]} {
	vdel -lib gate_work -all
}
vlib gate_work
vmap work gate_work

vlog -vlog01compat -work work +incdir+. {t1a_fs_pwm.vo}

vlog -vlog01compat -work work +incdir+/home/aditi/Eyantra/TASKS/Task1/t1a_fs_pwm/simulation/modelsim {/home/aditi/Eyantra/TASKS/Task1/t1a_fs_pwm/simulation/modelsim/tb.v}

vsim -t 1ps -L altera_ver -L cycloneive_ver -L gate_work -L work -voptargs="+acc"  tb

add wave *
view structure
view signals
run 40 us
