#include <fcntl.h>
#include <iostream>
#include <unistd.h>

#include "space_invaders/Colors.h"
#include "space_invaders/Graphics.h"

int main() {
  Sprites s;
  Graphics g(s);

  g.fillScreen(Colors::BLACK);

  Sprite *alien = s.getAlien(SPRITE_ALIEN_MID_OUT);
  constexpr int ALIEN_SIZE = 25;
  g.drawSprite(alien,
               GRAPHICS_WIDTH / 2 - (alien->getWidth() + 1) * ALIEN_SIZE / 2,
               GRAPHICS_HEIGHT / 2 - alien->getHeight() * ALIEN_SIZE / 2,
               ALIEN_SIZE, {128, 128, 128}, {0, 0, 0});
}