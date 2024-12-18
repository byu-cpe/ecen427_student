#include <fcntl.h>
#include <iostream>
#include <unistd.h>

#include "space_invaders/Graphics.h"

int main() {
  Sprites s;
  Graphics g(s);

  g.fillScreen(Colors::BLACK);

  struct timespec start, end;

  // Time drawing sprites with background color
  clock_gettime(CLOCK_MONOTONIC, &start);
  for (int i = 0; i < 100; i++) {
    g.drawSprite(s.getAlien(SPRITE_ALIEN_MID_OUT), 0, 100, 25, Colors::YELLOW,
                 Colors::ROYAL);
  }
  clock_gettime(CLOCK_MONOTONIC, &end);

  // Calculate time
  double time = (end.tv_sec - start.tv_sec) +
                (end.tv_nsec - start.tv_nsec) / 1000000000.0;
  std::cout << "Time for drawSprite() w   background color: " << time / 100
            << "s" << std::endl;

  // Time drawing sprites without background color
  clock_gettime(CLOCK_MONOTONIC, &start);
  for (int i = 0; i < 100; i++) {
    g.drawSprite(s.getAlien(SPRITE_ALIEN_MID_OUT), GRAPHICS_WIDTH / 2, 100, 25,
                 Colors::ROYAL);
  }
  clock_gettime(CLOCK_MONOTONIC, &end);

  time = (end.tv_sec - start.tv_sec) +
         (end.tv_nsec - start.tv_nsec) / 1000000000.0;
  std::cout << "Time for drawSprite() w/o background color: " << time / 100
            << "s" << std::endl;
}