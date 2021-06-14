#ifndef USERSPACE_DRIVERS_FILL_BITMAP_REGION_FILL_BITMAP_REGION
#define USERSPACE_DRIVERS_FILL_BITMAP_REGION_FILL_BITMAP_REGION

#include <stdbool.h>
#include <stdint.h>

int fill_bitmap_init(uint8_t *frame_buffer);
void fill_bitmap_region(uint16_t src_x, uint16_t src_y, uint16_t dest_x,
                        uint16_t dest_y, uint16_t width, uint16_t height,
                        bool fill_from_const, uint8_t const_R, uint8_t const_G,
                        uint8_t const_B);
bool fill_bitmap_region_is_done();

#endif /* USERSPACE_DRIVERS_FILL_BITMAP_REGION_FILL_BITMAP_REGION */
