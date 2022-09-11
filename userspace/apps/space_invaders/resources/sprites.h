#ifndef _SPRITES_H_
#define _SPRITES_H_

#include <stdint.h>

#include "../utils.h"

// define the column count of each sprite type (same as bit width)
#define SPRITES_16X7_COLS 16
#define SPRITES_12X10_COLS 12
#define SPRITES_12X8_COLS 12
#define SPRITES_15X8_COLS 15
#define SPRITES_24X18_COLS 24
#define SPRITES_6X6_COLS 6
#define SPRITES_1X5_COLS 1
#define SPRITES_3X5_COLS 3
#define SPRITES_5X5_COLS 5

// define the row count of each sprite type (also size of the arrays)
#define SPRITES_16X7_ROWS 7
#define SPRITES_12X10_ROWS 10
#define SPRITES_12X8_ROWS 8
#define SPRITES_15X8_ROWS 8
#define SPRITES_24X18_ROWS 18
#define SPRITES_6X6_ROWS 6
#define SPRITES_1X5_ROWS 5
#define SPRITES_3X5_ROWS 5
#define SPRITES_5X5_ROWS 5

extern const uint32_t sprite_ufo_16x7[SPRITES_16X7_ROWS];

extern const uint32_t sprite_alien_explosion_12x10[SPRITES_12X10_ROWS];
extern const uint32_t sprite_alien_top_in_12x8[SPRITES_12X8_ROWS];
extern const uint32_t sprite_alien_top_out_12x8[SPRITES_12X8_ROWS];
extern const uint32_t sprite_alien_middle_in_12x8[SPRITES_12X8_ROWS];
extern const uint32_t sprite_alien_middle_out_12x8[SPRITES_12X8_ROWS];
extern const uint32_t sprite_alien_bottom_in_12x8[SPRITES_12X8_ROWS];
extern const uint32_t sprite_alien_bottom_out_12x8[SPRITES_12X8_ROWS];

extern const uint32_t sprite_tank_15x8[SPRITES_15X8_ROWS];
extern const uint32_t sprite_tank_explosion1_15x8[SPRITES_15X8_ROWS];
extern const uint32_t sprite_tank_explosion2_15x8[SPRITES_15X8_ROWS];
extern const uint32_t sprite_tank_gone_15x8[SPRITES_15X8_ROWS];

extern const uint32_t sprite_bunker_24x18[SPRITES_24X18_ROWS];
extern const uint32_t sprite_bunkerDamage0_6x6[SPRITES_6X6_ROWS];
extern const uint32_t sprite_bunkerDamage1_6x6[SPRITES_6X6_ROWS];
extern const uint32_t sprite_bunkerDamage2_6x6[SPRITES_6X6_ROWS];
extern const uint32_t sprite_bunkerDamage3_6x6[SPRITES_6X6_ROWS];
extern const uint32_t sprite_bunkerDamage4_6x6[SPRITES_6X6_ROWS];

extern const uint32_t sprite_bunker_upper_left_gone_6x6[SPRITES_6X6_ROWS];
extern const uint32_t sprite_bunker_upper_right_gone_6x6[SPRITES_6X6_ROWS];
extern const uint32_t sprite_bunker_lower_left_gone_6x6[SPRITES_6X6_ROWS];
extern const uint32_t sprite_bunker_lower_right_gone_6x6[SPRITES_6X6_ROWS];

extern const uint32_t sprite_tankbullet_1x5[SPRITES_1X5_ROWS];
extern const uint32_t sprite_tankbullet_gone_1x5[SPRITES_1X5_ROWS];
extern const uint32_t sprite_alienbullet1_down_3x5[SPRITES_3X5_ROWS];
extern const uint32_t sprite_alienbullet1_up_3x5[SPRITES_3X5_ROWS];
extern const uint32_t sprite_alienbullet2_up_3x5[SPRITES_3X5_ROWS];
extern const uint32_t sprite_alienbullet2_down_3x5[SPRITES_3X5_ROWS];
extern const uint32_t sprite_alienbullet2_gone_3x5[SPRITES_3X5_ROWS];

extern const uint32_t sprite_letterA_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterB_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterC_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterD_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterE_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterF_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterG_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterH_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterI_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterJ_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterK_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterL_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterM_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterN_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterO_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterP_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterQ_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterR_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterS_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterT_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterU_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterV_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterW_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterX_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterY_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_letterZ_5x5[SPRITES_5X5_ROWS];

extern const uint32_t sprite_number0_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_number1_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_number2_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_number3_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_number4_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_number5_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_number6_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_number7_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_number8_5x5[SPRITES_5X5_ROWS];
extern const uint32_t sprite_number9_5x5[SPRITES_5X5_ROWS];

extern const uint32_t sprite_letterBLANK_5x5[SPRITES_5X5_ROWS];

#endif
