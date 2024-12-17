#ifndef APPS_SPACE_INVADERS_BUNKERS_H
#define APPS_SPACE_INVADERS_BUNKERS_H

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
#endif /* APPS_SPACE_INVADERS_BUNKERS_H */
