#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <stdint.h>
#include <string>
#include <vector>

#include "config.h"

// Use to draw the high score screen, accept user's high score name, and
// read/write the high scores file.
class HighScores {
public:
  // This is constructed at game over and is provided with the player's score.
  // This should determine the path to the high scores file and read the file
  // into the highScores.
  HighScores(uint32_t score);

private:
  // The score achieved by the player
  uint32_t score;

  // The string the player is entering, assuming they achieved a high scores
  // (initializes to all "A"s)
  std::string userEntry;

  // The current index the user is entering (0, 1, or 2)
  uint8_t entryIdx;

  // Tick counter and tick max used for blinking the entry letter
  uint32_t tickCnt;
  uint32_t tickCntMax;

  // Used to keep track of the blinking, whether the entryIdx character is being
  // shown or not.
  bool showChar;

  // Used to temporarily store the y-coordinate of the entry text.
  uint16_t nameEntryY;

  // The calculated file path to the high scores file.  This should not be
  // hard-coded, but should be located somewhere in your space_invaders
  // directory.  Use 'readlink("/proc/self/exe",...' to determine where your
  // executable is located, and then modify the string appopriately.  Tip:
  // readlink does not produce a null terminated string, so it's best to zero
  // out the buffer before calling it.
  std::string filePath;

  // The high scores list, read from the file and then written back out to the
  // file.
  std::vector<std::pair<std::string, uint32_t>> highScores;

public:
  // Used to draw the name entry screen.
  void drawUserEntry();

  // Tick the name entry screen
  void tickUserEntry();

  // Whether the user is done entering their initials.
  bool isUserEntryDone() { return entryIdx >= HIGH_SCORES_NUM_CHARS; };

  // Triggers the highScores to be written out to the file.
  void save();

  // Draw the high scores screen (shown after the user enters their initials, or
  // immediately after game over if a new high score is not achieved)
  void drawHighScores();
};

#endif /* HIGHSCORES_H */
