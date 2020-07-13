#ifndef __INTC_H__
#define __INTC_H__

#include <stdint.h>

#define INTC_SUCCESS 0

// Initializes the driver (opens UIO file and calls mmap)
// devDevice: The file path to the uio dev file
// Returns: A negative error code on error, INTC_SUCCESS otherwise
// This must be called before calling any other intc_* functions
int32_t intc_init(char devDevice[]);

// Called to exit the driver (unmap and close UIO file)
void intc_exit();

// This function will block until an interrupt occurrs
// Returns: Bitmask of activated interrupts
uint32_t intc_wait_for_interrupt();

// Acknowledge interrupt(s) in the interrupt controller
// irq_mask: Bitmask of interrupt lines to acknowledge.
void intc_ack_interrupt(uint32_t irq_mask);

// // Instruct the UIO to enable interrupts for this device in Linux
// // (see the UIO documentation for how to do this)
void intc_enable_uio_interrupts();

// Enable interrupt line(s)
// irq_mask: Bitmask of lines to enable
// This function only enables interrupt lines, ie, a 0 bit in irq_mask
//	will not disable the interrupt line
void intc_irq_enable(uint32_t irq_mask);

// Same as intc_irq_enable, except this disables interrupt lines
void intc_irq_disable(uint32_t irq_mask);

#endif /* __INTC_H__ */