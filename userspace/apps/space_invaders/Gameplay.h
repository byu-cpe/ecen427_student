#ifndef GAMEPLAY_H
#define GAMEPLAY_H

class Bunkers;
class Tank;
class Aliens;
class UFO;

// This class manages the normal gameplay of the game (but not the
// gameover/highscores screen)
class Gameplay {
public:
  Gameplay();

private:
  Bunkers *bunkers;
  Tank *tank;
  Aliens *aliens;
  UFO *ufo;

  // Check all collisions by calling all appropriate collision functions.  This
  // only needs to be done if some game object moved during the last tick.
  void checkCollisions();

public:
  // Draw everything at the beginning of the game
  void drawInit();

  // Tick the game
  void tick();

  // Return whether the game is over (all lives lost, or aliens reach the
  // bottom)
  bool isGameOver();
};

#endif /* GAMEPLAY_H */
