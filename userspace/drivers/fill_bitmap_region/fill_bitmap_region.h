#ifndef USERSPACE_DRIVERS_FILL_BITMAP_REGION_FILL_BITMAP_REGION
#define USERSPACE_DRIVERS_FILL_BITMAP_REGION_FILL_BITMAP_REGION

#include <stdbool.h>
#include <stdint.h>

// Initialize the accelerator driver (by calling
// XCopy_bitmap_region_Initialize), and set the frame buffer address.
int fill_bitmap_init(uint8_t *frame_buffer);

// Set various accelerator inputs, then start the accelerator
void fill_bitmap_region(uint16_t src_x, uint16_t src_y, uint16_t dest_x,
                        uint16_t dest_y, uint16_t width, uint16_t height,
                        bool fill_from_const, uint8_t const_R, uint8_t const_G,
                        uint8_t const_B);

// Return whether the accelerator is finished
bool fill_bitmap_region_is_done();

#endif /* USERSPACE_DRIVERS_FILL_BITMAP_REGION_FILL_BITMAP_REGION */
