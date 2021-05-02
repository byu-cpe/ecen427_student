HW_BITSTREAM = ../hw/ecen427.bit
LOCAL_BITSTREAM = ./ecen427.bit
BITSTREAM_BIN = $(LOCAL_BITSTREAM).bin
BITSTREAM_BIF = bitstream.bif

DTSI = ecen427.dtsi
DTSO = ecen427.dtbo

build: $(DTSO) $(BITSTREAM_BIN)

install: 
	sudo cp $(DTSO) /lib/firmware
	sudo cp $(BITSTREAM_BIN) /lib/firmware
	sudo /etc/init.d/configure_hardware.sh

$(DTSO): $(DTSI)
	dtc -O dtb -o $@ -b 0 -@ $^

$(BITSTREAM_BIN): $(LOCAL_BITSTREAM)
	bootgen -image $(BITSTREAM_BIF) -arch zynq -process_bitstream bin -w on

$(LOCAL_BITSTREAM): $(HW_BITSTREAM)
	cp $^ $@