create_hls_proj:
	vitis_hls proj.tcl

open_hls_proj:
	vitis_hls -p vitis_hls_proj

sw:
	gcc bitmap_accelerator.c bitmap_accelerator_test.c -o bitmap_accelerator
	./bitmap_accelerator