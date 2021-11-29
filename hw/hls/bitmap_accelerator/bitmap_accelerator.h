#ifndef HW_HLS_BITMAP_ACCELERATOR_BITMAP_ACCELERATOR
#define HW_HLS_BITMAP_ACCELERATOR_BITMAP_ACCELERATOR

#include <stdbool.h>
#include <stdint.h>

#define DISPLAY_W 640
#define DISPLAY_H 480
#define DISPLAY_BYTES_PER_PIXEL 3

void fill_bitmap_region(uint8_t *frame_buffer, uint16_t src_x, uint16_t src_y,
                        uint16_t dest_x, uint16_t dest_y, uint16_t width,
                        uint16_t height, bool fill_from_const, uint8_t const_R,
                        uint8_t const_G, uint8_t const_B);

#endif /* HW_HLS_BITMAP_ACCELERATOR_BITMAP_ACCELERATOR */
