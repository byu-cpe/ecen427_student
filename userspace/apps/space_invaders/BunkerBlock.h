#ifndef BUNKERBLOCK_H
#define BUNKERBLOCK_H

#include <stdint.h>

#include "GameObject.h"

#define BUNKER_BLOCK_MAX_DAMAGE 4

// One block of a Bunker.
class BunkerBlock : public GameObject {
public:
  // Construct a block at a given x,y.  Make sure this calls the parent
  // constructor.
  BunkerBlock(uint16_t x, uint16_t y);

private:
  // Track how much damage has occurred.
  uint8_t dmgLevel;

public:
  // Increase the damage level, and draw the appropriate damage.
  void inflictDamage();
};

#endif /* BUNKERBLOCK_H */
