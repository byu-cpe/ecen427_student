#ifndef USERSPACE_DRIVERS_AUDIO_AUDIO_CONFIG
#define USERSPACE_DRIVERS_AUDIO_AUDIO_CONFIG

#include <stdint.h>

// void config_audio_pll(int iic_index);
// void config_audio_codec(int iic_index);
void audio_config_init();

// 6-bit volume input (0 to 63)
void audio_config_set_volume(uint8_t volume);

#endif /* USERSPACE_DRIVERS_AUDIO_AUDIO_CONFIG */
