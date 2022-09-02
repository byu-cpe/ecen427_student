#ifndef SWITCHES
#define SWITCHES

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SWITCHES_SUCCESS 0  // value of an success
#define SWITCHES_0_MASK 0x1 // The mask for button zero
#define SWITCHES_1_MASK 0x2 // The mask for button one
#define SWITCHES_ALL_MASK 0x3
#define SWITCHES_CNT 2

// Initialize the driver
//  devFilePath: The file path to the uio dev file
//  Return: An error code on error, SWITCHES_SUCCESS otherwise
// This must be called before calling any other switches_* functions
//
//  Tip: This function won't be able to open the UIO device file unless the
//  program is run with ''sudo''.  This is easy to forget, so it is helpful to
//  code an error message into this function that says "Did you forget to
//  sudo?", if it cannot open the UIO file.
int32_t switches_init(const char *devFilePath);

// Return the current state of the switches
uint8_t switches_read();

// Call this on exit to clean up
void switches_exit();

// Enable GPIO interrupt output
void switches_enable_interrupts();

// Disable GPIO interrupt output
void switches_disable_interrupts();

// Return whether an interrupt is pending
bool switches_interrupt_pending();

// Acknowledge a pending interrupt
void switches_ack_interrupt();

#ifdef __cplusplus
}
#endif

#endif /* SWITCHES */
