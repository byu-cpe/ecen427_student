#ifndef APPS_SPACE_INVADERS_GLOBALS_H
#define APPS_SPACE_INVADERS_GLOBALS_H

#include "Bullets.h"
#include "Graphics.h"
#include "Lives.h"
#include "Score.h"
#include "Sprites.h"
#include "system.h"
#include "Audio.h"

// Track all global variables as static members of this class
class Globals
{
public:
  Globals();

private:
  static Graphics graphics;
  static Sprites sprites;
  static rgb_t backgroundColor;
  static Bullets bullets;
  static Score score;
  static Lives lives;
  static Audio audio;

public:
  static Graphics &getGraphics() { return graphics; }
  static Sprites &getSprites() { return sprites; }
  static rgb_t getBackgroundColor() { return backgroundColor; }
  static void setBackgroundColor(rgb_t color) { backgroundColor = color; }
  static Bullets &getBullets() { return bullets; }
  static double getTickPeriod() { return SYSTEM_FIT_PERIOD_SECONDS; }
  static Score &getScore() { return score; }
  static Lives &getLives() { return lives; }
  static Audio &getAudio() { return audio; }
};

#endif /* APPS_SPACE_INVADERS_GLOBALS_H */
