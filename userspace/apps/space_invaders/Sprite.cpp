#include "Sprite.h"

Sprite::Sprite(const uint32_t data[], uint8_t height, uint8_t width)
    : data(data), width(width), height(height) {}

bool Sprite::isFgPixel(uint8_t row, uint8_t col) {
  if (data[row] & (1 << col))
    return true;
  return false;
}
