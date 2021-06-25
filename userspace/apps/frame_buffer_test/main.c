#include <assert.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>

#include "../kernel/hdmi_ctrl/ecen427_ioctl.h"
#include "system.h"

#include "fill_bitmap_region/fill_bitmap_region.h"

#define ORIGIN_X 0
#define ORIGIN_Y 0
#define IGNORE 0

#define FILL_FROM_CONST true
#define BLACK 0
#define WHITE 255
#define SQUARE_SIZE 30

#define SQUARE0_XY 0
#define SQUARE1_XY 15
#define SQUARE2_XY 30

#define DISPLAY_MID_X (SYSTEM_DISPLAY_W / 2)
#define DISPLAY_MID_Y (SYSTEM_DISPLAY_H / 2)

#define COPY_SIZE (SQUARE_SIZE * 2)

// Run the frame buffer check program
// This draws red, green, and blue squares in the top-left of the screen
// (origin), and then copies this region to the middle of the screen.
int main() {
  printf("hi there\n");
  int fd;
  fd = open(SYSTEM_HDMI_FILE, O_RDWR);
  // Check that UIO file opened correctly.
  if (fd < 0) {
    printf("Cannot open %s. Did you sudo?\n", SYSTEM_HDMI_FILE);
    return fd;
  }

  uint8_t *base_addr = 0;
  int status = ioctl(fd, ECEN427_IOC_FRAME_BUFFER_ADDR, &base_addr);
  if (status) {
    printf("IOCTL error: %d\n", status);
  }
  printf("Frame buffer base address: %p\n", base_addr);

  status = fill_bitmap_init(base_addr);
  assert(!status);

  // Fill screen black
  fill_bitmap_region(IGNORE, IGNORE, ORIGIN_X, ORIGIN_Y, SYSTEM_DISPLAY_W,
                     SYSTEM_DISPLAY_H, FILL_FROM_CONST, BLACK, BLACK, BLACK);

  while (!fill_bitmap_region_is_done())
    ;

  // Make red square
  fill_bitmap_region(IGNORE, IGNORE, SQUARE0_XY, SQUARE0_XY, SQUARE_SIZE,
                     SQUARE_SIZE, FILL_FROM_CONST, WHITE, BLACK, BLACK);

  while (!fill_bitmap_region_is_done())
    ;

  // Make blue square
  fill_bitmap_region(IGNORE, IGNORE, SQUARE1_XY, SQUARE1_XY, SQUARE_SIZE,
                     SQUARE_SIZE, FILL_FROM_CONST, BLACK, WHITE, BLACK);

  while (!fill_bitmap_region_is_done())
    ;

  // Make green square
  fill_bitmap_region(IGNORE, IGNORE, SQUARE2_XY, SQUARE2_XY, SQUARE_SIZE,
                     SQUARE_SIZE, FILL_FROM_CONST, BLACK, BLACK, WHITE);

  while (!fill_bitmap_region_is_done())
    ;

  // Copy it all to another place
  fill_bitmap_region(ORIGIN_X, ORIGIN_Y, DISPLAY_MID_X, DISPLAY_MID_Y,
                     COPY_SIZE, COPY_SIZE, false, IGNORE, IGNORE, IGNORE);
  while (!fill_bitmap_region_is_done())
    ;
}