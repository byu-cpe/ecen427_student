#ifndef DRIVERS_BUTTONS_BUTTONS_H
#define DRIVERS_BUTTONS_BUTTONS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BUTTONS_SUCCESS 0
#define BUTTONS_0_MASK 0x1
#define BUTTONS_1_MASK 0x2
#define BUTTONS_2_MASK 0x4
#define BUTTONS_3_MASK 0x8
#define BUTTONS_ALL_MASK 0x0F
#define BUTTONS_CNT 4

// Initialize the driver
//  devFilePath: The file path to the uio dev file
//  Return: An error code on error, BUTTONS_SUCCESS otherwise
// This must be called before calling any other buttons_* functions
//
//  Tip: If this function cannot open the UIO device file, the hardware may
//  not be loaded, or the udev rules may not be installed.  It is helpful to
//  code an error message into this function that names the file it could not
//  open.
int32_t buttons_init(const char *devFilePath);

// Return the current state of the buttons
uint8_t buttons_read();

// Call this on exit to clean up
void buttons_exit();

// Enable GPIO interrupt output
void buttons_enable_interrupts();

// Disable GPIO interrupt output
void buttons_disable_interrupts();

// Return whether an interrupt is pending
bool buttons_interrupt_pending();

// Acknowledge a pending interrupt
void buttons_ack_interrupt();

#ifdef __cplusplus
}
#endif

#endif /* DRIVERS_BUTTONS_BUTTONS_H */
