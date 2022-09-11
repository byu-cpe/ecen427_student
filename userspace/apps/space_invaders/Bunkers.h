#ifndef BUNKERS_H
#define BUNKERS_H

#include <vector>

#include "Bunker.h"

// Tracks all Bunker objects in the game.
class Bunkers {
public:
  Bunkers();

private:
  std::vector<Bunker *> bunkers;

public:
  // Draw the bunker
  void draw();

  // Check collision between both player and enemy bullets and all bunkers.
  void checkCollisions();
};
#endif /* BUNKERS_H */
