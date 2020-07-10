# Linux Device Tree and Bootloader

The makefile in this directory allows you to build the bootloader and the linux device tree, and device tree overlays.

## Prerequisites
  1. Install the necessary packages:
```
sudo apt install device-tree-compiler libssl-dev flex bison
```	

_Note:_ If you are using a newer version of Ubuntu (18+ I think), you will need to install 
	``libssl1.0-dev`` instead of ``libssl-dev``
	
  2. Add the Xilinx tools to your ``PATH``:

	source /opt/Xilinx/Vivado/2017.4/settings64.sh


## Building the device tree

To modify the device tree, first make any desired modifications to the source files (dts/*) and then recompile the binary (dtb/devicetree.dtb) using ``make binary``.  You can do this on the PYNQ board, or your local machine.

Once built, you can copy the device tree over the old one:

```
sudo cp dtb/devicetree.dtb /boot/devicetree.dtb
```


## Building the bootloader

Building the bootloader requires the Xilinx tools, so it cannot be done on the PYNQ board.  Run ``make bootimg`` to build to bootloader.  It will be placed in ``boot/BOOT.bin``

Once built, you can copy the new bootloader using remote copy:

```
scp boot/BOOT.bin root@pynqIP:/boot/BOOT.bin
```


