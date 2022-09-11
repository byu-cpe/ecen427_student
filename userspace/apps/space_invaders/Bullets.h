#ifndef BULLETS_H
#define BULLETS_H

#include <list>
#include <stdint.h>

#include "config.h"

class Bullet;
class Tank;
class Alien;

// Class that tracks all bullets in the game
class Bullets {
public:
  Bullets();

private:
  // There can only be one player bullet, so this will either point to the
  // active player bullet, or will be a nullptr.
  Bullet *playerBullet;

  // All enemby bullets
  std::list<Bullet *> enemyBullets;

public:
  // Create new bullets
  void newPlayerBullet(Tank *tank);
  void newEnemyBullet(Alien *alien);

  // Get the player or enemy bullets
  Bullet *getPlayerBullet() { return playerBullet; }
  std::list<Bullet *> &getEnemyBullets() { return enemyBullets; }

  // Return whether the number of enemy bullets has reached the maximum.
  bool enemyBulletsMaxed() {
    return enemyBullets.size() >= BULLET_ENEMY_MAX_COUNT;
  }

  // Kill this bullet (deallocate and remove, updating playerBullet or
  // enemyBullets)
  void kill(Bullet *bullet);

public:
  // Tick the bullets, and return whether something moved.
  bool tick();
};

#endif /* BULLETS_H */
