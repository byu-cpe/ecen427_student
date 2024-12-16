#ifndef APPS_SPACE_INVADERS_COLORS_H
#define APPS_SPACE_INVADERS_COLORS_H

#include <cstdint>

// An RGB pixel/color
typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_t;

// Constants for colors
class Colors {
public:
  static const constexpr rgb_t BLACK = {0, 0, 0};
  static const constexpr rgb_t WHITE = {0xFF, 0xFF, 0xFF};
  static const constexpr rgb_t GREEN = {0, 0xFF, 0};
  static const constexpr rgb_t RED = {0xFF, 0, 0};
  static const constexpr rgb_t NAVY = {0, 46, 93};
  static const constexpr rgb_t ROYAL = {0, 61, 165};
  static const constexpr rgb_t PURPLE = {102, 45, 145};
  static const constexpr rgb_t YELLOW = {255, 255, 0};
};

#endif /* APPS_SPACE_INVADERS_COLORS_H */
