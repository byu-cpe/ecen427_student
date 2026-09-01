#ifndef APPS_SPACE_INVADERS_COLORS_H
#define APPS_SPACE_INVADERS_COLORS_H

#include <cstdint>

// An RGB pixel/color
typedef struct {
  uint8_t g;
  uint8_t b;
  uint8_t r;
} rgb_t;

// Constants for colors
class Colors {
public:
  static const constexpr rgb_t BLACK = {.g = 0, .b = 0, .r = 0};
  static const constexpr rgb_t WHITE = {.g = 0xFF, .b = 0xFF, .r = 0xFF};
  static const constexpr rgb_t GREEN = {.g = 0xFF, .b = 0, .r = 0};
  static const constexpr rgb_t RED = {.g = 0, .b = 0, .r = 0xFF};
  static const constexpr rgb_t NAVY = {.g = 46, .b = 93, .r = 0};
  static const constexpr rgb_t ROYAL = {.g = 61, .b = 165, .r = 0};
  static const constexpr rgb_t PURPLE = {.g = 45, .b = 145, .r = 102};
  static const constexpr rgb_t YELLOW = {.g = 255, .b = 0, .r = 255};
};

#endif /* APPS_SPACE_INVADERS_COLORS_H */
