#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <stdint.h>

#include "Graphics.h"
#include "Sprite.h"

// This is a base class for all objects in the game.
class GameObject {
public:
  // Make sure all subclasses call this constructor
  GameObject(Sprite *sprite, uint16_t x, uint16_t y, uint8_t size, rgb_t color);

private:
  // Object size, color
  uint8_t size;
  rgb_t color;

  // Whether object is alive.  Dead objects won't be drawn.
  bool alive;

protected:
  // Location and sprite of object.
  uint16_t x, y;
  Sprite *sprite;

  // Bring object back to life.  Make alive and redraw.
  void resurrect();

public:
  // Erase and redraw an object, at a new location and/or with a new sprite.
  //  - newSprite: new sprite to draw, or nullptr to not change the sprite.
  //  - delta_x/y: move object, input 0 to leave in same spot.
  void move(Sprite *newSprite, int16_t delta_x, int16_t delta_y);

  // Draw the object
  void draw();

  // Erase the object
  void erase();

  // Draw the object, but don't draw the background pixels (this is slower, but
  // is needed for the bunker damage)
  void drawNoBackground();

  // Kill the object, which should erase it.
  void kill();

  uint16_t getX() { return x; }
  uint16_t getY() { return y; }
  uint16_t getWidth() { return sprite->getWidth() * size; }
  uint16_t getHeight() { return sprite->getHeight() * size; }

  // Get the X midpoint
  uint16_t getMidX() { return x + getWidth() / 2; }

  // Get the bottom of the object (useful for aliens firing missiles)
  uint16_t getBottomY() { return y + getHeight(); }

  // Check whether the object is alive
  bool isAlive() { return alive; }

  // Check if this object is overlapping a given object.  This can be used to
  // handle all collisions in the game.
  bool isOverlapping(GameObject *object);
};

#endif /* GAMEOBJECT_H */
