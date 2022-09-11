#ifndef ALIENS_H
#define ALIENS_H

#include <vector>

#include "Alien.h"

// Class that tracks all aliens
class Aliens {
public:
  Aliens();

private:
  // All Alien objects, row by row, starting with top row
  std::vector<std::vector<Alien *>> aliens;

  // Tick counter and max ticks for moving the aliens
  uint32_t moveTickCnt;
  const uint32_t moveTickMax;

  // Tick counter and max ticks for firing an alien bullet
  uint32_t fireTickCnt;
  uint32_t fireTickMax;

  // Whether the aliens are moving left or right
  bool movingLeft;

  // The number of aliens left alive
  uint16_t numAliensAlive;

  // Whether the aliens have reached the bunkers, which triggers a game over.
  bool reachedBunker;

  // Returns the bottom most alien that is alive in a column, and nullptr if
  // they are all dead.
  Alien *getBottomAlienInColumn(uint8_t col);

public:
  // Initialize all aliens.  This can be called again when all aliens are dead
  // to reset the alien group.
  void initialize();

  // Draw all the aliens (probably only need to call this at the beginning)
  void draw();

  // Tick the alien group, and return whether something moved.
  bool tick();

  // Check for collisions between player bullet and aliens, killing player
  // bullet and alien when they are overlapping.
  void checkCollisions();

  // Generate a random number of ticks for firing the next alien bullet and
  // store in fireTickMax
  void generateRandomFireDelay();

  // Number of aliens alive
  uint16_t numAlive() { return numAliensAlive; }

  // Whether the aliens ahve reached the bottom of the screen (gamve over)
  bool reachedBottom() { return reachedBunker; }
};
#endif /* ALIENS_H */
