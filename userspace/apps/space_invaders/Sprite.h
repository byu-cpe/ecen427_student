#ifndef SPRITE_H
#define SPRITE_H

#include <cstdint>

// A graphical sprite, which contains a bitmap and width and height. (This only
// tracks the source image, not the GameObject which as an x,y location and
// size)
class Sprite {
public:
  // Construct a new sprite from bitmap data
  Sprite(const uint32_t data[], uint8_t height, uint8_t width);

private:
  uint8_t width;
  uint8_t height;
  const uint32_t *data;

public:
  uint8_t getWidth() { return width; }
  uint8_t getHeight() { return height; }

  // Return whether the given row and col idx has a pixel in the sprite.
  bool isFgPixel(uint8_t row, uint8_t col);
};

#endif /* SPRITE_H */
