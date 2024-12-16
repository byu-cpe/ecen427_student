#include "dma/dma.h"

#include "space_invaders/Graphics.h"

int main() {
  Sprites sprites;
  Graphics graphics(sprites);

  int error = dma_init();
  if (error) {
    printf("Error initializing DMA\n");
    return error;
  }

  graphics.fillScreen(Colors::BLACK);

  // Draw 1 large alien sprite on top-left of screen
  Sprite *alien = sprites.getAlien(SPRITE_ALIEN_MID_OUT);
  constexpr int ALIEN_SIZE = 25;
  graphics.drawSprite(alien, 0, 0, ALIEN_SIZE, Colors::GREEN, Colors::BLACK);

  // Copy to top-right of screen
  dma_start_sprite_copy(0, 0, GRAPHICS_WIDTH / 2, 0,
                        alien->getWidth() * ALIEN_SIZE,
                        alien->getHeight() * ALIEN_SIZE);
  while (dma_is_busy())
    ;

  // Copy to bottom-left of screen
  dma_start_sprite_copy(0, 0, 0, GRAPHICS_HEIGHT / 2,
                        alien->getWidth() * ALIEN_SIZE,
                        alien->getHeight() * ALIEN_SIZE);
  while (dma_is_busy())
    ;

  // Copy to bottom-right of screen
  dma_start_sprite_copy(0, 0, GRAPHICS_WIDTH / 2, GRAPHICS_HEIGHT / 2,
                        alien->getWidth() * ALIEN_SIZE,
                        alien->getHeight() * ALIEN_SIZE);
  while (dma_is_busy())
    ;

  dma_exit();
}