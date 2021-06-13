#include <assert.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>

#include "../kernel/hdmi_ctrl/ecen427_ioctl.h"
#include "system.h"

#include "copy_bitmap_region/copy_bitmap_region.h"

int main() {
  printf("hi there\n");
  int fd;
  fd = open(SYSTEM_HDMI_FILE, O_RDWR);
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

  status = copy_bitmap_init(base_addr);
  assert(!status);

  // Fill screen
  copy_bitmap_region(0, 0, 0, 0, 640, 480, true, 0, 0, 0);

  while (!copy_bitmap_region_is_done())
    ;

  // Make red square
  copy_bitmap_region(0, 0, 0, 0, 30, 30, true, 255, 0, 0);

  while (!copy_bitmap_region_is_done())
    ;

  // Make blue square
  copy_bitmap_region(0, 0, 15, 15, 30, 30, true, 0, 255, 0);

  while (!copy_bitmap_region_is_done())
    ;

  // Make green square
  copy_bitmap_region(0, 0, 30, 30, 30, 30, true, 0, 0, 255);

  while (!copy_bitmap_region_is_done())
    ;

  // Copy it all to another place
  copy_bitmap_region(0, 0, 320, 240, 60, 60, false, 0, 0, 0);
  while (!copy_bitmap_region_is_done())
    ;
}