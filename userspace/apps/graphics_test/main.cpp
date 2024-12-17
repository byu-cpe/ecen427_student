#include <fcntl.h>
#include <iostream>
#include <unistd.h>

#include "space_invaders/Colors.h"
#include "space_invaders/Graphics.h"

int main() {
  Sprites s;
  Graphics g(s);

  g.fillScreen(Colors::NAVY);

  // Draw "BYU" and "ECEN 427" centered at the top of the screen
  g.drawStrCentered("BYU", 50, 15, Colors::WHITE, Colors::NAVY);

  g.drawStrCentered("ECEN 427", 170, 10, Colors::WHITE, Colors::NAVY);

  // Draw UFO overtop of "ECEN 427"
  g.drawSprite(s.getUFO(), 115, 190, 6, Colors::RED);

  // Draw large alien with yellow tank w/ black background inside
  constexpr int TANK_SIZE = 3;
  constexpr int ALIEN_SIZE = 25;
  Sprite *tank = s.getTank(SPRITE_TANK);
  Sprite *alien = s.getAlien(SPRITE_ALIEN_MID_OUT);

  // Draw alien.  Add 1 to width because sprite is not centered.
  g.drawSprite(alien,
               GRAPHICS_WIDTH / 2 - (alien->getWidth() + 1) * ALIEN_SIZE / 2,
               260, ALIEN_SIZE, Colors::GREEN);

  // Draw tank
  g.drawSprite(tank, GRAPHICS_WIDTH / 2 - tank->getWidth() * TANK_SIZE / 2, 370,
               TANK_SIZE, Colors::YELLOW, Colors::BLACK);
}