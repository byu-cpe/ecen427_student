#ifndef INTC
#define INTC

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define INTC_SUCCESS 0

// This driver sits between two things, and has to talk to both of them:
//
//   The AXI Interrupt Controller hardware, which you reach by reading and
//   writing its registers through the pointer returned by mmap().
//
//   Linux (via the UIO driver) which you reach with read(), poll() and write() 
//   system calls on the UIO device file.  Linux owns the interrupt line, and 
//   decides when your program is allowed to hear about an interrupt.
//
// Most of the functions below need both.  Waiting for an interrupt means
// blocking on the device file until Linux reports one, and then reading a
// register to find out which lines actually fired.  Acknowledging an interrupt
// means clearing it in the hardware and then telling Linux you are ready for
// the next one.
//
// The part that catches people out is that Linux masks the interrupt line
// every time an interrupt arrives, and will not deliver another until
// userspace writes a 1 to the device file.  
// intc_init() and intc_ack_interrupt() should be responsible for doing that.

// Initializes the driver (opens UIO file and calls mmap)
// devDevice: The file path to the uio dev file
// Returns: A negative error code on error, INTC_SUCCESS otherwise
// This must be called before calling any other intc_* functions
//
//  Tip: If this function cannot open the UIO device file, the hardware may
//  not be loaded, or the udev rules may not be installed.  It is helpful to
//  code an error message into this function that names the file it could not
//  open.
int32_t intc_init(const char devDevice[]);

// Called to exit the driver (unmap and close UIO file)
void intc_exit();


// Enable interrupt line(s)
// irq_mask: Bitmask of lines to enable
// This function only enables interrupt lines, ie, a 0 bit in irq_mask
// will not disable the interrupt line. You normally call this once 
// during setup; the lines stay enabled.
void intc_irq_enable(uint32_t irq_mask);

// Same as intc_irq_enable, except this disables interrupt lines
void intc_irq_disable(uint32_t irq_mask);

// Block until an interrupt occurs, then access the intc hardware to determine
// and return which interrupt(s) fired.
// Returns: Bitmask of activated interrupts
uint32_t intc_wait_for_interrupt();

// The same as intc_wait_for_interrupt(), except it gives up after
// 'timeout' milliseconds instead of waiting forever.  Pass 0 to check without
// waiting at all.  If an interrupt is waiting, it is consumed and reported
// just as intc_wait_for_interrupt() would. 
// Returns: Bitmask of activated interrupts, 0 if no interrupt has occurred
uint32_t intc_try_wait_for_interrupt(int timeout);

// Finish handling an interrupt.  Call this once you are done with it.
// irq_mask: Bitmask of interrupt lines to acknowledge.
//
// This clears the interrupt in the intc hardware, and then tells Linux you
// are ready for the next one (the UIO documentation calls this re-enabling 
// the interrupt).  The order matters: the intc holds its output asserted until 
// it is cleared, so re-enabling Linux first would immediately produce a duplicate 
// interrupt.
void intc_ack_interrupt(uint32_t irq_mask);

#ifdef __cplusplus
}
#endif

#endif /* INTC */
