#ifndef UFO_H
#define UFO_H

#include <stdint.h>

#include "GameObject.h"

// The flying UFO object
class UFO : public GameObject {
public:
  UFO();

private:
  // Tick counter
  uint32_t tickCnt;

  // How often the UFO moves
  const uint32_t moveTickMax;

  // How long until the UFO appears (random)
  uint32_t hideTickMax;

  // UFO state
  typedef enum { HIDDEN, MOVING } state_t;
  state_t state;

  // Used to indicate to state machine to kill the UFO
  bool flagKill;

  // Calculate the random number of ticks until the UFO should appear
  uint32_t getRandomHideDelayTicks();

public:
  // Tick the UFO and return whether it moved
  bool tick();

  // Check for collisions between the player bullet and the UFO
  void checkCollisions();
};

#endif /* UFO_H */
