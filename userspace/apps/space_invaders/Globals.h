#ifndef APPS_SPACE_INVADERS_GLOBALS_H
#define APPS_SPACE_INVADERS_GLOBALS_H

#include "Audio.h"
#include "Bullets.h"
#include "Colors.h"
#include "Graphics.h"
#include "Lives.h"
#include "Score.h"
#include "Sprites.h"
#include "system.h"

// Track all global variables using Meyer's Singleton pattern
class Globals {
public:
  Globals() = delete;

  static Sprites &getSprites() {
    static Sprites sprites;
    return sprites;
  }

  static Graphics &getGraphics() {
    static Graphics graphics(getSprites());
    return graphics;
  }

  static rgb_t &getBackgroundColor() {
    static rgb_t backgroundColor = Colors::BLACK;
    return backgroundColor;
  }

  static void setBackgroundColor(rgb_t color) { getBackgroundColor() = color; }

  static Bullets &getBullets() {
    static Bullets bullets;
    return bullets;
  }

  static double getTickPeriod() { return SYSTEM_FIT_PERIOD_SECONDS; }

  static Score &getScore() {
    static Score score;
    return score;
  }

  static Lives &getLives() {
    static Lives lives;
    return lives;
  }

  static Audio &getAudio() {
    static Audio audio;
    return audio;
  }
};

#endif /* APPS_SPACE_INVADERS_GLOBALS_H */
