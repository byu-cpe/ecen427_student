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

  void tick();
  void playSound(std::string name, bool loop = false);
  void stopLoopedSound();
  bool isPlaying();

private:
  // File descriptor for the audio device
  int fd;

  // Tick counter for pauses between walk sounds
  int walk_pause_tick_cnt;

  // Special flag to help with UFO priority
  bool ufo_playing;

  std::map<std::string, std::vector<uint32_t>> sounds;

  void load_sound(std::string name, std::string filename);
};

#endif /* APPS_SPACE_INVADERS_AUDIO_H */
