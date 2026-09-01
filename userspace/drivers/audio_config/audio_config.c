#include "audio_config.h"

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "i2cps.h"

// ADAU register write values
#define R0_CLKSRC 0x08
#define R0_INFREQ 0x06
#define RECORD_MIXER_MUTED 0x00
#define DIFFERENTIAL_21DB 0xB3
#define R10_MBIAS_EN 0x01

#define STD_I2C_MSG_SIZE 3
#define BASE_CODEC_I2C_ADDR 0x40
#define BASE_ADDR_OFFSET 0
#define REG_ADDR_OFFSET 1
#define DATA_ADDR_OFFSET 2

// Slave address for the ADAU audio controller 8
#define IIC_SLAVE_ADDR 0x3B

// the i2c dev num we need to talk to
#define IIC_INDEX 1

// ADAU internal registers
enum audio_adau1761_regs {
  R0_CLOCK_CONTROL = 0x00,
  R1_PLL_CONTROL = 0x02,
  R2_DIGITAL_MIC_JACK_DETECTION_CONTROL = 0x08,
  R3_RECORD_POWER_MANAGEMENT = 0x09,
  R4_RECORD_MIXER_LEFT_CONTROL_0 = 0x0A,
  R5_RECORD_MIXER_LEFT_CONTROL_1 = 0x0B,
  R6_RECORD_MIXER_RIGHT_CONTROL_0 = 0x0C,
  R7_RECORD_MIXER_RIGHT_CONTROL_1 = 0x0D,
  R8_LEFT_DIFFERENTIAL_INPUT_VOLUME_CONTROL = 0x0E,
  R9_RIGHT_DIFFERENTIAL_INPUT_VOLUME_CONTROL = 0x0F,
  R10_RECORD_MICROPHONE_BIAS_CONTROL = 0x10,
  R11_ALC_CONTROL_0 = 0x11,
  R12_ALC_CONTROL_1 = 0x12,
  R13_ALC_CONTROL_2 = 0x13,
  R14_ALC_CONTROL_3 = 0x14,
  R15_SERIAL_PORT_CONTROL_0 = 0x15,
  R16_SERIAL_PORT_CONTROL_1 = 0x16,
  R17_CONVERTER_CONTROL_0 = 0x17,
  R18_CONVERTER_CONTROL_1 = 0x18,
  R19_ADC_CONTROL = 0x19,
  R20_LEFT_INPUT_DIGITAL_VOLUME = 0x1A,
  R21_RIGHT_INPUT_DIGITAL_VOLUME = 0x1B,
  R22_PLAYBACK_MIXER_LEFT_CONTROL_0 = 0x1C,
  R23_PLAYBACK_MIXER_LEFT_CONTROL_1 = 0x1D,
  R24_PLAYBACK_MIXER_RIGHT_CONTROL_0 = 0x1E,
  R25_PLAYBACK_MIXER_RIGHT_CONTROL_1 = 0x1F,
  R26_PLAYBACK_LR_MIXER_LEFT_LINE_OUTPUT_CONTROL = 0x20,
  R27_PLAYBACK_LR_MIXER_RIGHT_LINE_OUTPUT_CONTROL = 0x21,
  R28_PLAYBACK_LR_MIXER_MONO_OUTPUT_CONTROL = 0x22,
  R29_PLAYBACK_HEADPHONE_LEFT_VOLUME_CONTROL = 0x23,
  R30_PLAYBACK_HEADPHONE_RIGHT_VOLUME_CONTROL = 0x24,
  R31_PLAYBACK_LINE_OUTPUT_LEFT_VOLUME_CONTROL = 0x25,
  R32_PLAYBACK_LINE_OUTPUT_RIGHT_VOLUME_CONTROL = 0x26,
  R33_PLAYBACK_MONO_OUTPUT_CONTROL = 0x27,
  R34_PLAYBACK_POP_CLICK_SUPPRESSION = 0x28,
  R35_PLAYBACK_POWER_MANAGEMENT = 0x29,
  R36_DAC_CONTROL_0 = 0x2A,
  R37_DAC_CONTROL_1 = 0x2B,
  R38_DAC_CONTROL_2 = 0x2C,
  R39_SERIAL_PORT_PAD_CONTROL = 0x2D,
  R40_CONTROL_PORT_PAD_CONTROL_0 = 0x2F,
  R41_CONTROL_PORT_PAD_CONTROL_1 = 0x30,
  R42_JACK_DETECT_PIN_CONTROL = 0x31,
  R67_DEJITTER_CONTROL = 0x36,
  R58_SERIAL_INPUT_ROUTE_CONTROL = 0xF2,
  R59_SERIAL_OUTPUT_ROUTE_CONTROL = 0xF3,
  R61_DSP_ENABLE = 0xF5,
  R62_DSP_RUN = 0xF6,
  R63_DSP_SLEW_MODES = 0xF7,
  R64_SERIAL_PORT_SAMPLING_RATE = 0xF8,
  R65_CLOCK_ENABLE_0 = 0xF9,
  R66_CLOCK_ENABLE_1 = 0xFA
};

// borrowed from Xilinx, modified to meet coding standard
/******************************************************************************
 * Function to write 8 bits to one of the registers from the audio
 * controller.
 * @param   u8RegAddr is the register address.
 * @param   u8Data is the data byte to write.
 * @param   iic_fd is the file descriptor for /dev/i2c-x
 * @return  none.
 *****************************************************************************/
void write_audio_reg(unsigned char u8RegAddr, unsigned char u8Data,
                     int iic_fd) {
  unsigned char u8TxData[STD_I2C_MSG_SIZE];
  u8TxData[BASE_ADDR_OFFSET] = BASE_CODEC_I2C_ADDR;
  u8TxData[REG_ADDR_OFFSET] = u8RegAddr;
  u8TxData[DATA_ADDR_OFFSET] = u8Data;
  if (writeI2C_asFile(iic_fd, u8TxData, STD_I2C_MSG_SIZE) < 0) {
    printf("Unable to write audio register.\n");
  }
}

// borrowed from Xilinx, no modifications
/******************************************************************************
 * Function to configure the audio PLL.
 * @param   iic_index is the i2c index in /dev list.
 * @return  none.
 *****************************************************************************/
void config_audio_pll(int iic_index) {
  unsigned char u8TxData[8], u8RxData[6];
  int iic_fd;
  iic_fd = setI2C(iic_index, IIC_SLAVE_ADDR);
  if (iic_fd < 0) {
    printf("Unable to set I2C %d.\n", iic_index);
    return;
  }

  // Disable Core Clock
  write_audio_reg(R0_CLOCK_CONTROL, 0x0E, iic_fd);
  /*  MCLK = 10 MHz
   *  R = 0100 = 4, N = 0x023C = 572, M = 0x0271 = 625
   *  PLL required output = 1024x48 KHz = 49.152 MHz
   *  PLLout/MCLK         = 49.152 MHz/10 MHz = 4.9152 MHz
   *                      = R + (N/M)
   *                      = 4 + (572/625)
   */
  // Register write address [15:8]
  u8TxData[0] = 0x40;
  // Register write address [7:0]
  u8TxData[1] = 0x02;
  // byte 6 - M[15:8]
  u8TxData[2] = 0x02;
  // byte 5 - M[7:0]
  u8TxData[3] = 0x71;
  // byte 4 - N[15:8]
  u8TxData[4] = 0x02;
  // byte 3 - N[7:0]
  u8TxData[5] = 0x3C;
  // byte 2 - bits 6:3 = R[3:0], 2:1 = X[1:0], 0 = PLL operation mode
  u8TxData[6] = 0x21;
  // byte 1 - 1 = PLL Lock, 0 = Core clock enable
  u8TxData[7] = 0x03;
  // Write bytes to PLL control register R1 at 0x4002
  if (writeI2C_asFile(iic_fd, u8TxData, 8) < 0) {
    printf("Unable to write I2C %d.\n", iic_index);
    perror("oops");
  }

  // Poll PLL Lock bit
  u8TxData[0] = 0x40;
  u8TxData[1] = 0x02;
  do {
    if (writeI2C_asFile(iic_fd, u8TxData, 2) < 0) {
      printf("Unable to write I2C %d.\n", iic_index);
    }
    if (readI2C_asFile(iic_fd, u8RxData, 6) < 0) {
      printf("Unable to read I2C %d.\n", iic_index);
    }
  } while ((u8RxData[5] & 0x02) == 0);

  /* Clock control register:  bit 3        CLKSRC = PLL Clock input
   *                          bit 2:1      INFREQ = 1024 x fs
   *                          bit 0        COREN = Core Clock enabled
   */
  write_audio_reg(R0_CLOCK_CONTROL, 0x0F, iic_fd);

  if (unsetI2C(iic_fd) < 0) {
    printf("Unable to unset I2C %d.\n", iic_index);
  }
}

/******************************************************************************
 * Function to configure the audio codec.
 * @param   iic_index is the i2c index in /dev list.
 * @return  none.
 *****************************************************************************/
void config_audio_codec(int iic_index) {
  int iic_fd;
  iic_fd = setI2C(iic_index, IIC_SLAVE_ADDR);
  if (iic_fd < 0) {
    printf("Unable to set I2C %d.\n", iic_index);
  }

  /*
   * Input path control registers are configured
   * in select_mic and select_line_in
   */

  // Mute Mixer1 and Mixer2 here, enable when MIC and Line In used
  write_audio_reg(R4_RECORD_MIXER_LEFT_CONTROL_0, RECORD_MIXER_MUTED, iic_fd);
  write_audio_reg(R6_RECORD_MIXER_RIGHT_CONTROL_0, RECORD_MIXER_MUTED, iic_fd);
  // Set LDVOL and RDVOL to 21 dB and Enable left and right differential
  write_audio_reg(R8_LEFT_DIFFERENTIAL_INPUT_VOLUME_CONTROL, DIFFERENTIAL_21DB,
                  iic_fd);
  write_audio_reg(R9_RIGHT_DIFFERENTIAL_INPUT_VOLUME_CONTROL, DIFFERENTIAL_21DB,
                  iic_fd);
  // Enable MIC bias
  write_audio_reg(R10_RECORD_MICROPHONE_BIAS_CONTROL, R10_MBIAS_EN, iic_fd);
  // Enable ALC control and noise gate
  write_audio_reg(R14_ALC_CONTROL_3, 0x20, iic_fd);
  // Put CODEC in Master mode
  write_audio_reg(R15_SERIAL_PORT_CONTROL_0, 0x01, iic_fd);
  // Enable ADC on both channels, normal polarity and ADC high-pass filter
  write_audio_reg(R19_ADC_CONTROL, 0x33, iic_fd);
  // Mute play back Mixer3 and Mixer4 and enable when output is required
  write_audio_reg(R22_PLAYBACK_MIXER_LEFT_CONTROL_0, 0x00, iic_fd);
  write_audio_reg(R24_PLAYBACK_MIXER_RIGHT_CONTROL_0, 0x00, iic_fd);
  // Mute left input to mixer3 (R23) and right input to mixer4 (R25)
  write_audio_reg(R23_PLAYBACK_MIXER_LEFT_CONTROL_1, 0x00, iic_fd);
  write_audio_reg(R25_PLAYBACK_MIXER_RIGHT_CONTROL_1, 0x00, iic_fd);
  // Mute left and right channels output; enable them when output is needed
  write_audio_reg(R29_PLAYBACK_HEADPHONE_LEFT_VOLUME_CONTROL, 0xE5, iic_fd);
  write_audio_reg(R30_PLAYBACK_HEADPHONE_RIGHT_VOLUME_CONTROL, 0xE5, iic_fd);
  // Enable play back right and left channels
  write_audio_reg(R35_PLAYBACK_POWER_MANAGEMENT, 0x03, iic_fd);
  // Enable DAC for both channels
  write_audio_reg(R36_DAC_CONTROL_0, 0x03, iic_fd);
  // Set SDATA_In to DAC
  write_audio_reg(R58_SERIAL_INPUT_ROUTE_CONTROL, 0x01, iic_fd);
  // Set SDATA_Out to ADC
  write_audio_reg(R59_SERIAL_OUTPUT_ROUTE_CONTROL, 0x01, iic_fd);
  // Enable DSP and DSP Run
  write_audio_reg(R61_DSP_ENABLE, 0x01, iic_fd);
  write_audio_reg(R62_DSP_RUN, 0x01, iic_fd);
  /*
   * Enable Digital Clock Generator 0 and 1.
   * Generator 0 generates sample rates for the ADCs, DACs, and DSP.
   * Generator 1 generates BCLK and LRCLK for the serial port.
   */
  write_audio_reg(R65_CLOCK_ENABLE_0, 0x7F, iic_fd);
  write_audio_reg(R66_CLOCK_ENABLE_1, 0x03, iic_fd);

  // Unmute left and right DAC, enable Mixer3 and Mixer4
  write_audio_reg(R22_PLAYBACK_MIXER_LEFT_CONTROL_0, 0x21, iic_fd);
  write_audio_reg(R24_PLAYBACK_MIXER_RIGHT_CONTROL_0, 0x41, iic_fd);

  if (unsetI2C(iic_fd) < 0) {
    printf("Unable to unset I2C %d.\n", iic_index);
  }
}

void audio_config_init() {
  config_audio_pll(IIC_INDEX);
  config_audio_codec(IIC_INDEX);

  int iic_fd;
  iic_fd = setI2C(IIC_INDEX, IIC_SLAVE_ADDR);
  if (iic_fd < 0) {
    printf("Unable to set I2C %d.\n", IIC_INDEX);
  }

  // Unmute left and right DAC, enable Mixer3 and Mixer4
  write_audio_reg(R22_PLAYBACK_MIXER_LEFT_CONTROL_0, 0x21, iic_fd);
  write_audio_reg(R24_PLAYBACK_MIXER_RIGHT_CONTROL_0, 0x41, iic_fd);
  // Enable Left/Right Headphone out
  write_audio_reg(R29_PLAYBACK_HEADPHONE_LEFT_VOLUME_CONTROL, 0xE7, iic_fd);
  write_audio_reg(R30_PLAYBACK_HEADPHONE_RIGHT_VOLUME_CONTROL, 0xE7, iic_fd);

  if (unsetI2C(iic_fd) < 0) {
    printf("Unable to unset I2C %d.\n", IIC_INDEX);
  }
}

#define VOLUME_UNMUTE 0x02
#define VOLUME_EN 0x01 // the mask for the volume
#define VOLUME_SHIFT 2 // amount to shift by when changing the volume

void audio_config_set_volume(uint8_t volume_level) {
  // get a handle on the audio codec
  int32_t iic_fd = setI2C(IIC_INDEX, IIC_SLAVE_ADDR);
  if (iic_fd < 0) {
    printf("Unable to set I2C %d.\n", IIC_INDEX);
  }

  uint8_t volume_muted = (volume_level << VOLUME_SHIFT) | VOLUME_EN;
  uint8_t volume = volume_muted | VOLUME_UNMUTE;

  // Set new volume, muted
  write_audio_reg(R29_PLAYBACK_HEADPHONE_LEFT_VOLUME_CONTROL, volume_muted,
                  iic_fd);
  write_audio_reg(R30_PLAYBACK_HEADPHONE_RIGHT_VOLUME_CONTROL, volume_muted,
                  iic_fd);

  // Wait 5ms then unmute
  usleep(5000);
  write_audio_reg(R29_PLAYBACK_HEADPHONE_LEFT_VOLUME_CONTROL, volume, iic_fd);
  write_audio_reg(R30_PLAYBACK_HEADPHONE_RIGHT_VOLUME_CONTROL, volume, iic_fd);

  // release the codec handle
  if (unsetI2C(iic_fd) < 0) {
    printf("Unable to unset I2C %d.\n", IIC_INDEX);
  }
}