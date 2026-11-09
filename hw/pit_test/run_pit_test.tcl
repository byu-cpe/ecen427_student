# Run the PIT AXI stress test (pit_test_tb.sv) against ip_repo/pit/pit.sv.
# Run from the hw directory:
#   make test_pit        run the test in batch mode
#   make test_pit_gui    run it in the xsim waveform viewer
# Simulation files and the log (sim.log) go in hw/pit_test_proj.
# Optional -tclargs: "gui", and/or the path of a different pit.sv.

set hw_dir [file normalize [file join [file dirname [info script]] ..]]
set pit_sv [file join $hw_dir ip_repo pit pit.sv]
set tb [file join $hw_dir pit_test pit_test_tb.sv]
set gui 0
foreach arg $argv {
    if {$arg eq "gui"} {
        set gui 1
    } else {
        set pit_sv [file normalize $arg]
    }
}

# The simulator tools that come with this Vivado
set bin [file join $::env(XILINX_VIVADO) bin]
set work [file join $hw_dir pit_test_proj]
file delete -force $work
file mkdir $work
cd $work
puts "Testing $pit_sv"

proc print_file {name} {
    set f [open $name]
    puts [read $f]
    close $f
}

if {[catch {exec $bin/xvlog -sv $pit_sv $tb >& compile.log}]} {
    print_file compile.log
    puts "COMPILE FAILED"
    exit 1
}
if {[catch {exec $bin/xelab pit_test_tb -s pit_test -debug typical >& elab.log}]} {
    print_file elab.log
    puts "ELABORATION FAILED"
    exit 1
}

if {$gui} {
    set f [open gui.tcl w]
    puts $f "log_wave -recursive *\nrun all"
    close $f
    catch {exec $bin/xsim pit_test -gui -tclbatch gui.tcl >& sim_gui.log}
    exit 0
}

catch {exec $bin/xsim pit_test -R >& sim.log}
set f [open sim.log]
set lines [split [read $f] "\n"]
close $f
foreach line [lsearch -all -inline -regexp $lines {^PASS|^FAIL|ERROR|WARNING \(|^Tests passed}] {
    puts $line
}
if {[lsearch -regexp $lines {PIT TEST RESULT: ALL TESTS PASSED}] >= 0} {
    puts "PIT TEST RESULT: ALL TESTS PASSED"
    exit 0
}
puts "PIT TEST RESULT: FAILED (full log: $work/sim.log; debug with make test_pit_gui)"
exit 1
