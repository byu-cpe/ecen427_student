#define SYSTEM_INTC_IRQ_FIT_MASK 0x01
#define SYSTEM_INTC_IRQ_BUTTONS_MASK 0x02
#define SYSTEM_INTC_IRQ_SWITCHES_MASK 0x04
#define SYSTEM_INTC_IRQ_DMA_MASK 0x08
#define SYSTEM_INTC_IRQ_PIT_MASK 0x10

// These names are created by the udev rules in kernel/99-ecen427.rules.  They
// are symlinks to the matching /dev/uioN node.  Use these instead of a uio
// number, which changes if hardware is added or removed.
#define SYSTEM_LEDS_UIO_FILE "/dev/ecen427/leds"
#define SYSTEM_BUTTONS_UIO_FILE "/dev/ecen427/buttons"
#define SYSTEM_SWITCHES_UIO_FILE "/dev/ecen427/switches"
#define SYSTEM_RGBLEDS_UIO_FILE "/dev/ecen427/rgbleds"
#define SYSTEM_INTC_UIO_FILE "/dev/ecen427/intc"
#define SYSTEM_DMA_UIO_FILE "/dev/ecen427/dma"
#define SYSTEM_HDMI_FILE "/dev/ecen427/hdmi"
#define SYSTEM_DMA_DESC_FILE "/dev/ecen427/dma_desc"

#define SYSTEM_FIT_PERIOD_SECONDS 0.01667

#define SYSTEM_DISPLAY_W 640
#define SYSTEM_DISPLAY_H 480

#define AUDIO_SAMPLE_RATE 48000