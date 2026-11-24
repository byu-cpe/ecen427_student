// This file is used for grading -- do not modify it. Any changes will be
// discarded and the original file will be used when your lab is graded.

#include "dma/dma.h"

#include "space_invaders/Graphics.h"

#include <cstdio>
#include <ctime>
#include <unistd.h>

static constexpr int NUM_SPRITES = 1000;
static constexpr int SPRITE_SIZE = 25;

// Seconds on the given clock.  CLOCK_MONOTONIC is elapsed (wall-clock) time;
// CLOCK_PROCESS_CPUTIME_ID is the CPU time this process has used.
static double now(clockid_t clock) {
  struct timespec t;
  clock_gettime(clock, &t);
  return t.tv_sec + t.tv_nsec / 1e9;
}

static void print_cpu_frequency() {
  FILE *f = fopen("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq", "r");
  unsigned int khz;
  if (f && fscanf(f, "%u", &khz) == 1)
    printf("CPU frequency: %u MHz\n", khz / 1000);
  else
    printf("CPU frequency: 650 MHz (cpufreq_427 module not loaded)\n");
  if (f)
    fclose(f);
}

int main() {
  Sprites sprites;
  Graphics graphics(sprites);

  dma_init();

  graphics.fillScreen(Colors::BLACK);

  Sprite *sprite = sprites.getAlien(SPRITE_ALIEN_TOP_IN);
  uint16_t width = sprite->getWidth() * SPRITE_SIZE;
  uint16_t height = sprite->getHeight() * SPRITE_SIZE;

  print_cpu_frequency();
  printf("%d sprites per mode\n\n", NUM_SPRITES);
  printf("%-36s %10s %10s\n", "Mode", "Elapsed s", "CPU s");

  for (int mode = 0; mode < 3; mode++) {
    const char *name = "";
    double wall_start = now(CLOCK_MONOTONIC);
    double cpu_start = now(CLOCK_PROCESS_CPUTIME_ID);

    for (int i = 0; i < NUM_SPRITES; i++) {
      if (mode == 0) {
        name = "CPU draws the sprites";
        graphics.drawSprite(sprite, 0, 0, SPRITE_SIZE, Colors::GREEN,
                            Colors::BLACK);
        continue;
      }

      dma_start_sprite_copy(0, 0, GRAPHICS_WIDTH / 2, 0, width, height);
      if (mode == 1) {
        // Ask the DMA engine "are you done?" as fast as possible.
        name = "DMA, CPU polls in a tight loop";
        while (dma_is_busy())
          ;
      } else {
        // Sleep between checks, so the CPU is idle while the DMA works.
        name = "DMA, CPU sleeps between checks";
        while (dma_is_busy())
          usleep(100);
      }
    }

    double wall = now(CLOCK_MONOTONIC) - wall_start;
    double cpu = now(CLOCK_PROCESS_CPUTIME_ID) - cpu_start;
    printf("%-36s %10.3f %10.3f\n", name, wall, cpu);
  }

  dma_exit();
}
