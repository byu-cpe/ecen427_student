# Linux Device Tree and Bootloader

The Makefile in this directory allows you to build the Linux Device Tree Overlay, as well as the bitstream .bin file. 

Note: The full device tree that is loaded when by Linux early in the boot process is provided in `pynq.dts`.  We will not be modifying this, as it requires rebuilding the entire boot image, and modifying the bootloader files on the SD card.  Rather, we will use a *device tree overlay*, which allows us to make runtime additions to the base device tree.  This overlay is provided in `ecen427.dtsi`.

## Prerequisites
  1. Install the necessary packages (this is already done on the lab computers):

      sudo apt install device-tree-compiler 

  2. Add the Xilinx tools to your ``PATH``:

	    source /tools/Xilinx/Vivado/2020.2/settings64.sh


## Building the device tree and hardware binary

(This should be done on a lab machine, or your local Linux computer with Vivado installed)

To modify the device tree: 
  * First make any desired modifications to the device tree source (`ecen427.dtbi`) and to your bitstream (`hw/ecen427.bit`)
  * Compile using ``make build``
  * This will produce:
      * The device tree overlay binary (`ecen427.dtbo`) 
      * The bitstream binary (`ecen427.bit.bin`)
  * Push these new files up to Github.


## Installing the Hardware

(This should be done on your PYNQ board)

1. Pull down the new `ecen427.dtbo` and `ecen427.bit.bin`.

1. To install the hardware, go into the `device_tree` directory, and run `sudo make install`.

	This will immediately replace the existing hardware bitstream on the board, and will install your device tree overlay.  This change is permanent; if the board is rebooted, it will automatically load the new bitstream and device tree at boot time.

*Note:* There seems to be a bug with the video hardware, and you may notice wrong colors or other problems when changing the hardware on-the-fly.  Just reboot your board and it should be resolved.

