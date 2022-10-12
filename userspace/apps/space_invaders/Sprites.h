#ifndef SPRITES_H
#define SPRITES_H

#include <map>
#include <vector>

#include "resources/sprites.h"

class Sprite;

// Types of alien sprites
typedef enum {
  SPRITE_ALIEN_TOP_IN,
  SPRITE_ALIEN_TOP_OUT,
  SPRITE_ALIEN_MID_IN,
  SPRITE_ALIEN_MID_OUT,
  SPRITE_ALIEN_BOT_IN,
  SPRITE_ALIEN_BOT_OUT,
} sprite_alien_type_t;

// Types of tank sprites
typedef enum {
  SPRITE_TANK,
  SPRITE_TANK_EXPLOSION1,
  SPRITE_TANK_EXPLOSION2
} sprite_tank_type_t;

// Types of bullet sprites
typedef enum {
  SPRITE_BULLET_TANK,
  SPRITE_BULLET_ALIEN1_DOWN,
  SPRITE_BULLET_ALIEN1_UP,
  SPRITE_BULLET_ALIEN2_DOWN,
  SPRITE_BULLET_ALIEN2_UP
} sprite_bullet_type_t;

class Sprites {
public:
  Sprites();
  ~Sprites();

  // UFO sprite
  Sprite *getUFO() { return ufo; }

  // Get the full bunker sprite (this is a large sprite containing all bunker
  // blocks together)
  Sprite *getBunker() { return bunker; }

  // Get the damage pattern of a bunker block for a given damage level. dmgLevel
  // = 0, no damage, dmgLevel = 4, solid sprite.
  Sprite *getBunkerDmg(uint8_t dmgLevel);

  // Get a sprite for a given char.  Only uppercase and space are provided.
  Sprite *getChar(char letter);

  // Get the sprite given the enum type.
  Sprite *getAlien(sprite_alien_type_t alien_type);
  Sprite *getAlienExplosion() { return explosion; }
  Sprite *getTank(sprite_tank_type_t);
  Sprite *getBullet(sprite_bullet_type_t);

  // Return the height of a char sprite of size 1
  uint16_t getCharHeight() { return SPRITES_5X5_ROWS; }

private:
  std::map<char, Sprite *> chars;
  std::map<sprite_alien_type_t, Sprite *> aliens;
  std::map<sprite_tank_type_t, Sprite *> tanks;
  std::map<sprite_bullet_type_t, Sprite *> bullets;
  std::vector<Sprite *> bunkerDmg;
  Sprite *ufo;
  Sprite *explosion;
  Sprite *bunker;
};
#endif /* SPRITES_H */
