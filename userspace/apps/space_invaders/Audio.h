#ifndef APPS_SPACE_INVADERS_AUDIO_H
#define APPS_SPACE_INVADERS_AUDIO_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

class Audio {
public:
  Audio();
  ~Audio();

  void playWalkSound();
  void playSound(std::string name, bool loop = false);
  void stopLoopedSound();
  bool isPlaying();

private:
  // File descriptor for the audio device
  int fd;

  // Which of the four walk sounds to play next
  int next_walk_sound;

  // Special flag to help with UFO priority
  bool ufo_playing;

  std::map<std::string, std::vector<uint32_t>> sounds;

  void load_sound(std::string name, std::string filename);
};

#endif /* APPS_SPACE_INVADERS_AUDIO_H */
