#include "dma/dma.h"

#include "space_invaders/Graphics.h"

int main() {
  Sprites sprites;
  Graphics graphics(sprites);

  int error = dma_init();

  graphics.fillScreen(Colors::BLACK);

  // Measure time to draw 100 sprites
  Sprite *sprite = sprites.getAlien(SPRITE_ALIEN_TOP_IN);
  struct timespec start, end;
  constexpr int SPRITE_SIZE = 25;

  clock_gettime(CLOCK_MONOTONIC, &start);
  for (int i = 0; i < 100; i++) {
    graphics.drawSprite(sprite, 0, 0, SPRITE_SIZE, Colors::GREEN,
                        Colors::BLACK);
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("Time to draw 100 sprites: %f s\n",
         (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9);

  clock_gettime(CLOCK_MONOTONIC, &start);
  for (int i = 0; i < 100; i++) {
    dma_start_sprite_copy(0, 0, GRAPHICS_WIDTH / 2, 0,
                          sprite->getWidth() * SPRITE_SIZE,
                          sprite->getHeight() * SPRITE_SIZE);
    while (dma_is_busy())
      ;
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("Time to DMA 100 sprites: %f s\n",
         (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9);

  printf("DMA transfer complete\n");

  dma_exit();
}