#ifndef LIVES_H
#define LIVES_H

#include <vector>

#include "config.h"

class Tank;

// Used to track and draw the number of player lives.
class Lives {
public:
  Lives() : numLives(LIVES_AT_START) {}

private:
  // Number of lives the player has.
  uint8_t numLives;

  // The lives can be drawn in the top-right using Tank objects.  Even though
  // they won't be part of the gameplay, it's fine to use these objects as long
  // as you don't tick them.
  std::vector<Tank *> tankLives;

  // Keep track of the x-coordinate where the first tank life is drawn.  Helpful
  // for drawing/erasing new lives in the future.
  uint16_t xDrawTankStart;

  // Draw a new life.  If tankLives is empty, you can use xDrawTankStart to
  // determine where to draw it, otherwise, just get the last tank in the
  // tankLives list and use that x-coordinate to calcuate where to draw the next
  // one.
  void drawNewLife();

public:
  // Draw the lives at the start of the game
  void draw();

  // Whether the game is over due to running out of lives
  bool isGameOver() { return numLives == 0; }

  // Trigger losing a life and erasing a tank sprite
  void loseALife();

  // Trigger gaining a life (happens when all aliens are destroyed); however,
  // make sure not to increase lives past the max number of lives.
  void gainALife();
};

#endif /* LIVES_H */
