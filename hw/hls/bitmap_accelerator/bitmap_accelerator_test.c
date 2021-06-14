#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bitmap_accelerator.h"
#include "test_bitmaps/copy_195_302_to_0_0_size_17_19.h"
#include "test_bitmaps/copy_55_85_to_200_300_size_5_7.h"
#include "test_bitmaps/rgb_1_2_3_rect_at_600_400_size_1_79.h"
#include "test_bitmaps/rgb_50_75_100_rect_at_50_75_size_15_25.h"

uint8_t pixel_buf[DISPLAY_W * DISPLAY_H * DISPLAY_BYTES_PER_PIXEL];

void fill_pixel_buf(uint8_t val) { memset(pixel_buf, val, sizeof(pixel_buf)); }

bool verify_bitmap(uint8_t *golden, uint8_t *test) {
  int errors = 0;

  int i = 0;
  for (int y = 0; y < DISPLAY_H; y++) {
    for (int x = 0; x < DISPLAY_W; x++) {
      for (int p = 0; p < DISPLAY_BYTES_PER_PIXEL; p++) {
        if (golden[i] != test[i]) {
          printf("Mistmatch at (x,y,rgb)=(%d,%d,%d). Golden=%d, Yours=%d\n", x,
                 y, p, golden[i], test[i]);
          errors++;
        }
        i++;
      }
    }
  }
  return errors;
}

int main() {

  // Create RGB=(1, 2, 3) rectangle at (600, 400) with (w,h)=(1, 79)
  printf("Test 1. Create RGB=(1, 2, 3) rectangle at (600, 400) with (w,h)=(1, "
         "79)\n");
  fill_pixel_buf(0);
  fill_bitmap_region(pixel_buf, 0, 0, 600, 400, 1, 79, true, 1, 2, 3);
  if (verify_bitmap(rgb_1_2_3_rect_at_600_400_size_1_79, pixel_buf)) {
    printf("Test 1 failed.\n");
    return 1;
  } else {
    printf("Passed.\n");
  }

  // Create RGB=(50, 75, 100) rectangle at (50, 75) with (w,h)=(15, 25)
  printf("Test 2. Create RGB=(50, 75, 100) rectangle at (50, 75) with "
         "(w,h)=(15, 25)\n");
  fill_pixel_buf(0);
  fill_bitmap_region(pixel_buf, 0, 0, 50, 75, 15, 25, true, 50, 75, 100);
  if (verify_bitmap(rgb_50_75_100_rect_at_50_75_size_15_25, pixel_buf)) {
    printf("Test 2 failed.\n");
    return 1;
  } else {
    printf("Passed.\n");
  }

  // Copy rectangle from (55, 85) to (200, 300) with (w,h) = (5, 7)
  printf("Test 3. Copy rectangle from (55, 85) to (200, 300) with (w,h) = (5, "
         "7)\n");
  fill_bitmap_region(pixel_buf, 55, 85, 200, 300, 5, 7, false, 0, 0, 0);
  if (verify_bitmap(copy_55_85_to_200_300_size_5_7, pixel_buf)) {
    printf("Test 3 failed.\n");
    return 1;
  } else {
    printf("Passed.\n");
  }

  // Copy rectangle from (195, 302) to (0, 0) with (w,h) = (17, 19)
  printf("Test 4. Copy rectangle from (195, 302) to (0, 0) with (w,h) = (17, "
         "19)\n");
  fill_bitmap_region(pixel_buf, 195, 302, 0, 0, 17, 19, false, 0, 0, 0);
  if (verify_bitmap(copy_195_302_to_0_0_size_17_19, pixel_buf)) {
    printf("Test 4 failed.\n");
    return 1;
  } else {
    printf("Passed.\n");
  }

  return 0;
}