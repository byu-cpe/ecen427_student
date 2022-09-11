#ifndef BUNKER_H
#define BUNKER_H

#include <stdint.h>
#include <vector>

#include "BunkerBlock.h"
#include "GameObject.h"
#include "Graphics.h"

class Bullet;

// Class representing one player bunker
class Bunker : public GameObject {
public:
  // Create bunker at given x,y location. Make sure this calls the parent
  // constructor.
  Bunker(uint16_t x, uint16_t y);

private:
  uint16_t x, y;
  uint8_t size;

  // A bunker is comprised of several BunkerBlocks
  std::vector<BunkerBlock *> bunkerBlocks;

public:
  // Check collision between both player and enemy bullets and the bunker.
  bool checkBulletCollision(Bullet *bullet);
};

#endif /* BUNKER_H */
