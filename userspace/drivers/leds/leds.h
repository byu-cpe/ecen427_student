#ifndef DRIVERS_LEDS_LEDS_H
#define DRIVERS_LEDS_LEDS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LEDS_SUCCESS 0
#define LEDS_0_MASK 0x1
#define LEDS_1_MASK 0x2
#define LEDS_2_MASK 0x4
#define LEDS_3_MASK 0x8
#define LEDS_ALL_MASK 0x0F
#define LEDS_CNT 4

// Initialize the driver
//  devFilePath: The file path to the uio dev file
//  Return: An error code on error, LEDS_SUCCESS otherwise
// This must be called before calling any other leds_* functions
int32_t leds_init(const char *devFilePath);

// Set the LEDs.  Bit i of value controls LED i (1 = on, 0 = off).
void leds_write(uint8_t value);

// Return the value most recently written to the LEDs
uint8_t leds_read();

// Call this on exit to clean up
void leds_exit();

#ifdef __cplusplus
}
#endif

#endif /* DRIVERS_LEDS_LEDS_H */
