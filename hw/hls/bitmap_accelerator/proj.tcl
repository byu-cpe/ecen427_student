set hls_prj vitis_hls_proj

# Open/reset the project
open_project ${hls_prj} -reset

# Top function of the design is "digitrec"
set_top fill_bitmap_region

# Add design and testbench files
add_files bitmap_accelerator.c 
add_files -tb bitmap_accelerator_test.c

open_solution "solution1"

# Use Zynq device
set_part {xc7z020clg484-1}

# Target clock period is 10ns
create_clock -period 10
