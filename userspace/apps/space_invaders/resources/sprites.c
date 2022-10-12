#include "sprites.h"

#include <stdint.h>

#include "../utils.h"

// Must define UTILS_UTILS_PACKWORD__ for each of the different bit-widths.

// clang-format off

const uint32_t sprite_ufo_16x7[] =
{
	UTILS_PACKWORD_16(0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0),
	UTILS_PACKWORD_16(0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0),
	UTILS_PACKWORD_16(0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0),
	UTILS_PACKWORD_16(0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0),
	UTILS_PACKWORD_16(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	UTILS_PACKWORD_16(0,0,1,1,1,0,0,1,1,0,0,1,1,1,0,0),
	UTILS_PACKWORD_16(0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0)
};

const uint32_t sprite_alien_explosion_12x10[] =
{
	UTILS_PACKWORD_12(0,0,0,0,0,0,1,0,0,0,0,0),
	UTILS_PACKWORD_12(0,0,0,1,0,0,1,0,0,0,1,0),
	UTILS_PACKWORD_12(1,0,0,1,0,0,0,0,0,1,0,0),
	UTILS_PACKWORD_12(0,1,0,0,1,0,0,0,1,0,0,0),
	UTILS_PACKWORD_12(0,0,0,0,0,0,0,0,0,0,1,1),
	UTILS_PACKWORD_12(1,1,0,0,0,0,0,0,0,0,0,0),
	UTILS_PACKWORD_12(0,0,0,1,0,0,0,1,0,0,1,0),
	UTILS_PACKWORD_12(0,0,1,0,0,0,0,0,1,0,0,1),
	UTILS_PACKWORD_12(0,1,0,0,0,1,0,0,1,0,0,0),
	UTILS_PACKWORD_12(0,0,0,0,0,1,0,0,0,0,0,0)
};

const uint32_t sprite_alien_top_in_12x8[] =
{
	UTILS_PACKWORD_12(0,0,0,0,0,1,1,0,0,0,0,0),
	UTILS_PACKWORD_12(0,0,0,0,1,1,1,1,0,0,0,0),
	UTILS_PACKWORD_12(0,0,0,1,1,1,1,1,1,0,0,0),
	UTILS_PACKWORD_12(0,0,1,1,0,1,1,0,1,1,0,0),
	UTILS_PACKWORD_12(0,0,1,1,1,1,1,1,1,1,0,0),
	UTILS_PACKWORD_12(0,0,0,1,0,1,1,0,1,0,0,0),
	UTILS_PACKWORD_12(0,0,1,0,0,0,0,0,0,1,0,0),
	UTILS_PACKWORD_12(0,0,0,1,0,0,0,0,1,0,0,0)
};

const uint32_t sprite_alien_top_out_12x8[] =
{
	UTILS_PACKWORD_12(0,0,0,0,0,1,1,0,0,0,0,0),
	UTILS_PACKWORD_12(0,0,0,0,1,1,1,1,0,0,0,0),
	UTILS_PACKWORD_12(0,0,0,1,1,1,1,1,1,0,0,0),
	UTILS_PACKWORD_12(0,0,1,1,0,1,1,0,1,1,0,0),
	UTILS_PACKWORD_12(0,0,1,1,1,1,1,1,1,1,0,0),
	UTILS_PACKWORD_12(0,0,0,0,1,0,0,1,0,0,0,0),
	UTILS_PACKWORD_12(0,0,0,1,0,1,1,0,1,0,0,0),
	UTILS_PACKWORD_12(0,0,1,0,1,0,0,1,0,1,0,0)
};

const uint32_t sprite_alien_middle_in_12x8[] =
{
	UTILS_PACKWORD_12(0,0,0,1,0,0,0,0,0,1,0,0),
	UTILS_PACKWORD_12(0,0,0,0,1,0,0,0,1,0,0,0),
	UTILS_PACKWORD_12(0,0,0,1,1,1,1,1,1,1,0,0),
	UTILS_PACKWORD_12(0,0,1,1,0,1,1,1,0,1,1,0),
	UTILS_PACKWORD_12(0,1,1,1,1,1,1,1,1,1,1,1),
	UTILS_PACKWORD_12(0,1,1,1,1,1,1,1,1,1,1,1),
	UTILS_PACKWORD_12(0,1,0,1,0,0,0,0,0,1,0,1),
	UTILS_PACKWORD_12(0,0,0,0,1,1,0,1,1,0,0,0)
};

const uint32_t sprite_alien_middle_out_12x8[] =
{
	UTILS_PACKWORD_12(0,0,0,1,0,0,0,0,0,1,0,0),
	UTILS_PACKWORD_12(0,1,0,0,1,0,0,0,1,0,0,1),
	UTILS_PACKWORD_12(0,1,0,1,1,1,1,1,1,1,0,1),
	UTILS_PACKWORD_12(0,1,1,1,0,1,1,1,0,1,1,1),
	UTILS_PACKWORD_12(0,1,1,1,1,1,1,1,1,1,1,1),
	UTILS_PACKWORD_12(0,0,1,1,1,1,1,1,1,1,1,0),
	UTILS_PACKWORD_12(0,0,0,1,0,0,0,0,0,1,0,0),
	UTILS_PACKWORD_12(0,0,1,0,0,0,0,0,0,0,1,0)
};

const uint32_t sprite_alien_bottom_in_12x8[] =
{
	UTILS_PACKWORD_12(0,0,0,0,1,1,1,1,0,0,0,0),
	UTILS_PACKWORD_12(0,1,1,1,1,1,1,1,1,1,1,0),
	UTILS_PACKWORD_12(1,1,1,1,1,1,1,1,1,1,1,1),
	UTILS_PACKWORD_12(1,1,1,0,0,1,1,0,0,1,1,1),
	UTILS_PACKWORD_12(1,1,1,1,1,1,1,1,1,1,1,1),
	UTILS_PACKWORD_12(0,0,1,1,1,0,0,1,1,1,0,0),
	UTILS_PACKWORD_12(0,1,1,0,0,1,1,0,0,1,1,0),
	UTILS_PACKWORD_12(0,0,1,1,0,0,0,0,1,1,0,0)
};

const uint32_t sprite_alien_bottom_out_12x8[] =
{
	UTILS_PACKWORD_12(0,0,0,0,1,1,1,1,0,0,0,0),
	UTILS_PACKWORD_12(0,1,1,1,1,1,1,1,1,1,1,0),
	UTILS_PACKWORD_12(1,1,1,1,1,1,1,1,1,1,1,1),
	UTILS_PACKWORD_12(1,1,1,0,0,1,1,0,0,1,1,1),
	UTILS_PACKWORD_12(1,1,1,1,1,1,1,1,1,1,1,1),
	UTILS_PACKWORD_12(0,0,0,1,1,0,0,1,1,0,0,0),
	UTILS_PACKWORD_12(0,0,1,1,0,1,1,0,1,1,0,0),
	UTILS_PACKWORD_12(1,1,0,0,0,0,0,0,0,0,1,1)
};

const uint32_t sprite_tank_15x8[] =
{
	UTILS_PACKWORD_15(0,0,0,0,0,0,0,1,0,0,0,0,0,0,0),
	UTILS_PACKWORD_15(0,0,0,0,0,0,1,1,1,0,0,0,0,0,0),
	UTILS_PACKWORD_15(0,0,0,0,0,0,1,1,1,0,0,0,0,0,0),
	UTILS_PACKWORD_15(0,1,1,1,1,1,1,1,1,1,1,1,1,1,0),
	UTILS_PACKWORD_15(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	UTILS_PACKWORD_15(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	UTILS_PACKWORD_15(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	UTILS_PACKWORD_15(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1)
};


// Shape of the entire bunker.
const uint32_t sprite_bunker_24x18[] =
{
	UTILS_PACKWORD_24(0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0),
	UTILS_PACKWORD_24(0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0),
	UTILS_PACKWORD_24(0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0),
	UTILS_PACKWORD_24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	UTILS_PACKWORD_24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	UTILS_PACKWORD_24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	UTILS_PACKWORD_24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	UTILS_PACKWORD_24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	UTILS_PACKWORD_24(1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1),
	UTILS_PACKWORD_24(1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1),
	UTILS_PACKWORD_24(1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1),
	UTILS_PACKWORD_24(1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1),
	UTILS_PACKWORD_24(1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1),
	UTILS_PACKWORD_24(1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1),
	UTILS_PACKWORD_24(1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1),
	UTILS_PACKWORD_24(1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1),
	UTILS_PACKWORD_24(1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1),
	UTILS_PACKWORD_24(1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1)
};

// These are the blocks that comprise the bunker and each time a bullet
// strikes one of these blocks, you erode the block as you sequence through
// these patterns.
const uint32_t sprite_bunkerDamage0_6x6[] = {
	UTILS_PACKWORD_6(0,0,0,0,0,0),
	UTILS_PACKWORD_6(0,0,0,0,0,0),
	UTILS_PACKWORD_6(0,0,0,0,0,0),
	UTILS_PACKWORD_6(0,0,0,0,0,0),
	UTILS_PACKWORD_6(0,0,0,0,0,0),
	UTILS_PACKWORD_6(0,0,0,0,0,0)
};
const uint32_t sprite_bunkerDamage1_6x6[] = {
	UTILS_PACKWORD_6(0,1,1,0,0,0),
	UTILS_PACKWORD_6(0,0,0,0,0,1),
	UTILS_PACKWORD_6(1,1,0,1,0,0),
	UTILS_PACKWORD_6(1,0,0,0,0,0),
	UTILS_PACKWORD_6(0,0,1,1,0,0),
	UTILS_PACKWORD_6(0,0,0,0,1,0)
};

const uint32_t sprite_bunkerDamage2_6x6[] = {
	UTILS_PACKWORD_6(1,1,1,0,1,0),
	UTILS_PACKWORD_6(1,0,1,0,0,1),
	UTILS_PACKWORD_6(1,1,0,1,1,1),
	UTILS_PACKWORD_6(1,0,0,0,0,0),
	UTILS_PACKWORD_6(0,1,1,1,0,1),
	UTILS_PACKWORD_6(0,1,1,0,1,0)
};

const uint32_t sprite_bunkerDamage3_6x6[] = {
	UTILS_PACKWORD_6(1,1,1,1,1,1),
	UTILS_PACKWORD_6(1,0,1,1,0,1),
	UTILS_PACKWORD_6(1,1,0,1,1,1),
	UTILS_PACKWORD_6(1,1,0,1,1,0),
	UTILS_PACKWORD_6(0,1,1,1,0,1),
	UTILS_PACKWORD_6(1,1,1,1,1,1)
};

const uint32_t sprite_bunkerDamage4_6x6[] = {
	UTILS_PACKWORD_6(1,1,1,1,1,1),
	UTILS_PACKWORD_6(1,1,1,1,1,1),
	UTILS_PACKWORD_6(1,1,1,1,1,1),
	UTILS_PACKWORD_6(1,1,1,1,1,1),
	UTILS_PACKWORD_6(1,1,1,1,1,1),
	UTILS_PACKWORD_6(1,1,1,1,1,1)
};

const uint32_t sprite_bunker_upper_left_gone_6x6[] = {
	UTILS_PACKWORD_6(0,0,0,1,1,1),
	UTILS_PACKWORD_6(0,0,1,1,1,1),
	UTILS_PACKWORD_6(0,1,1,1,1,1),
	UTILS_PACKWORD_6(1,1,1,1,1,1),
	UTILS_PACKWORD_6(1,1,1,1,1,1),
	UTILS_PACKWORD_6(1,1,1,1,1,1)
};

const uint32_t sprite_bunker_upper_right_gone_6x6[] = {
	UTILS_PACKWORD_6(1,1,1,0,0,0),
	UTILS_PACKWORD_6(1,1,1,1,0,0),
	UTILS_PACKWORD_6(1,1,1,1,1,0),
	UTILS_PACKWORD_6(1,1,1,1,1,1),
	UTILS_PACKWORD_6(1,1,1,1,1,1),
	UTILS_PACKWORD_6(1,1,1,1,1,1)
};

const uint32_t sprite_bunker_lower_left_gone_6x6[] = {
	UTILS_PACKWORD_6(1,1,1,1,1,1),
	UTILS_PACKWORD_6(1,1,1,1,1,1),
	UTILS_PACKWORD_6(0,0,1,1,1,1),
	UTILS_PACKWORD_6(0,0,0,1,1,1),
	UTILS_PACKWORD_6(0,0,0,0,1,1),
	UTILS_PACKWORD_6(0,0,0,0,0,1)
};

const uint32_t sprite_bunker_lower_right_gone_6x6[] = {
	UTILS_PACKWORD_6(1,1,1,1,1,1),
	UTILS_PACKWORD_6(1,1,1,1,1,1),
	UTILS_PACKWORD_6(1,1,1,1,0,0),
	UTILS_PACKWORD_6(1,1,1,0,0,0),
	UTILS_PACKWORD_6(1,1,0,0,0,0),
	UTILS_PACKWORD_6(1,0,0,0,0,0)
};

const uint32_t sprite_tank_explosion1_15x8[] = {
	UTILS_PACKWORD_15(0,0,0,0,1,0,0,0,0,0,0,0,0,0,0),
	UTILS_PACKWORD_15(0,0,1,0,0,0,0,1,0,0,1,0,0,0,0),
	UTILS_PACKWORD_15(0,0,0,0,1,0,1,0,0,1,0,1,0,0,0),
	UTILS_PACKWORD_15(0,0,1,0,0,0,0,0,0,0,0,0,1,0,0),
	UTILS_PACKWORD_15(0,0,0,0,0,1,0,1,1,0,0,0,0,0,0),
	UTILS_PACKWORD_15(1,0,0,1,1,1,1,1,1,1,1,0,0,0,0),
	UTILS_PACKWORD_15(0,0,1,1,1,1,1,1,1,1,1,1,0,0,0),
	UTILS_PACKWORD_15(1,1,1,1,1,1,1,1,1,1,1,1,1,0,0)
};

const uint32_t sprite_tank_explosion2_15x8[] = {
	UTILS_PACKWORD_15(1,0,0,0,0,0,1,0,0,0,0,0,1,0,0),
	UTILS_PACKWORD_15(0,0,0,1,0,0,0,0,0,0,0,0,0,0,0),
	UTILS_PACKWORD_15(0,1,0,0,0,0,1,0,0,0,0,0,1,0,0),
	UTILS_PACKWORD_15(0,0,0,0,0,1,0,0,0,0,1,0,0,0,1),
	UTILS_PACKWORD_15(1,0,0,0,1,1,0,0,1,0,0,0,0,0,0),
	UTILS_PACKWORD_15(0,0,0,1,1,1,1,1,1,1,0,0,1,0,0),
	UTILS_PACKWORD_15(0,0,1,1,1,1,1,1,1,1,1,0,0,0,0),
	UTILS_PACKWORD_15(1,1,1,1,1,1,1,1,1,1,1,1,1,0,0)
};

const uint32_t sprite_tank_gone_15x8[] = {
	UTILS_PACKWORD_15(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	UTILS_PACKWORD_15(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	UTILS_PACKWORD_15(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	UTILS_PACKWORD_15(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	UTILS_PACKWORD_15(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	UTILS_PACKWORD_15(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	UTILS_PACKWORD_15(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	UTILS_PACKWORD_15(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
};

const uint32_t sprite_tankbullet_1x5[] = {
	UTILS_PACKWORD_1(1),
	UTILS_PACKWORD_1(1),
	UTILS_PACKWORD_1(1),
	UTILS_PACKWORD_1(1),
	UTILS_PACKWORD_1(1)
};

const uint32_t sprite_tankbullet_gone_1x5[] = {
	UTILS_PACKWORD_1(0),
	UTILS_PACKWORD_1(0),
	UTILS_PACKWORD_1(0),
	UTILS_PACKWORD_1(0),
	UTILS_PACKWORD_1(0)
};

const uint32_t sprite_alienbullet1_down_3x5[] = {
	UTILS_PACKWORD_3(0,1,0),
	UTILS_PACKWORD_3(0,1,0),
	UTILS_PACKWORD_3(0,1,0),
	UTILS_PACKWORD_3(1,1,1),
	UTILS_PACKWORD_3(0,1,0)
};

const uint32_t sprite_alienbullet1_up_3x5[] = {
	UTILS_PACKWORD_3(0,1,0),
	UTILS_PACKWORD_3(1,1,1),
	UTILS_PACKWORD_3(0,1,0),
	UTILS_PACKWORD_3(0,1,0),
	UTILS_PACKWORD_3(0,1,0)
};

const uint32_t sprite_alienbullet2_up_3x5[] = {
	UTILS_PACKWORD_3(0,1,0),
	UTILS_PACKWORD_3(1,0,0),
	UTILS_PACKWORD_3(0,1,0),
	UTILS_PACKWORD_3(0,0,1),
	UTILS_PACKWORD_3(0,1,0)
};

const uint32_t sprite_alienbullet2_down_3x5[] = {
	UTILS_PACKWORD_3(0,1,0),
	UTILS_PACKWORD_3(0,0,1),
	UTILS_PACKWORD_3(0,1,0),
	UTILS_PACKWORD_3(1,0,0),
	UTILS_PACKWORD_3(0,1,0)
};


const uint32_t sprite_alienbullet2_gone_3x5[] = {
	UTILS_PACKWORD_3(0,0,0),
	UTILS_PACKWORD_3(0,0,0),
	UTILS_PACKWORD_3(0,0,0),
	UTILS_PACKWORD_3(0,0,0),
	UTILS_PACKWORD_3(0,0,0),
};

const uint32_t sprite_letterA_5x5[] = {
	UTILS_PACKWORD_5(0,1,1,1,0),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,0,1)
};

const uint32_t sprite_letterB_5x5[] = {
	UTILS_PACKWORD_5(1,1,1,1,0),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,1,1,1,0)
};

const uint32_t sprite_letterC_5x5[] = {
	UTILS_PACKWORD_5(0,1,1,1,1),
	UTILS_PACKWORD_5(1,0,0,0,0),
	UTILS_PACKWORD_5(1,0,0,0,0),
	UTILS_PACKWORD_5(1,0,0,0,0),
	UTILS_PACKWORD_5(0,1,1,1,1)
};

const uint32_t sprite_letterD_5x5[] = {
	UTILS_PACKWORD_5(1,1,1,1,0),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,1,1,1,0)
};

const uint32_t sprite_letterE_5x5[] = {
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(1,0,0,0,0),
	UTILS_PACKWORD_5(1,1,1,1,0),
	UTILS_PACKWORD_5(1,0,0,0,0),
	UTILS_PACKWORD_5(1,1,1,1,1)
};

const uint32_t sprite_letterF_5x5[] = {
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(1,0,0,0,0),
	UTILS_PACKWORD_5(1,1,1,1,0),
	UTILS_PACKWORD_5(1,0,0,0,0),
	UTILS_PACKWORD_5(1,0,0,0,0)
};

const uint32_t sprite_letterG_5x5[] = {
	UTILS_PACKWORD_5(0,1,1,1,1),
	UTILS_PACKWORD_5(1,0,0,0,0),
	UTILS_PACKWORD_5(1,0,0,1,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(0,1,1,1,0)
};

const uint32_t sprite_letterH_5x5[] = {
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,0,1)
};

const uint32_t sprite_letterI_5x5[] = {
	UTILS_PACKWORD_5(0,0,1,0,0),
	UTILS_PACKWORD_5(0,0,1,0,0),
	UTILS_PACKWORD_5(0,0,1,0,0),
	UTILS_PACKWORD_5(0,0,1,0,0),
	UTILS_PACKWORD_5(0,0,1,0,0)
};

const uint32_t sprite_letterJ_5x5[] = {
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(0,0,1,0,0),
	UTILS_PACKWORD_5(0,0,1,0,0),
	UTILS_PACKWORD_5(0,0,1,0,0),
	UTILS_PACKWORD_5(1,1,1,0,0)
};

const uint32_t sprite_letterK_5x5[] = {
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,1,0),
	UTILS_PACKWORD_5(1,1,1,0,0),
	UTILS_PACKWORD_5(1,0,0,1,0),
	UTILS_PACKWORD_5(1,0,0,0,1)
};

const uint32_t sprite_letterL_5x5[] = {
	UTILS_PACKWORD_5(1,0,0,0,0),
	UTILS_PACKWORD_5(1,0,0,0,0),
	UTILS_PACKWORD_5(1,0,0,0,0),
	UTILS_PACKWORD_5(1,0,0,0,0),
	UTILS_PACKWORD_5(1,1,1,1,1)
};

const uint32_t sprite_letterM_5x5[] = {
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,1,0,1,1),
	UTILS_PACKWORD_5(1,0,1,0,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,0,1)
};

const uint32_t sprite_letterN_5x5[] = {
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,1,0,0,1),
	UTILS_PACKWORD_5(1,0,1,0,1),
	UTILS_PACKWORD_5(1,0,0,1,1),
	UTILS_PACKWORD_5(1,0,0,0,1)
};

const uint32_t sprite_letterO_5x5[] = {
	UTILS_PACKWORD_5(0,1,1,1,0),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(0,1,1,1,0)
};

const uint32_t sprite_letterP_5x5[] = {
	UTILS_PACKWORD_5(0,1,1,1,0),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(1,0,0,0,0),
	UTILS_PACKWORD_5(1,0,0,0,0)
};

const uint32_t sprite_letterQ_5x5[] = {
	UTILS_PACKWORD_5(0,1,1,1,0),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,1,0),
	UTILS_PACKWORD_5(0,1,1,0,1)
};

const uint32_t sprite_letterR_5x5[] = {
	UTILS_PACKWORD_5(1,1,1,1,0),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,1,1,1,0),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,0,1)
};

const uint32_t sprite_letterS_5x5[] = {
	UTILS_PACKWORD_5(0,1,1,1,1),
	UTILS_PACKWORD_5(1,0,0,0,0),
	UTILS_PACKWORD_5(0,1,1,1,0),
	UTILS_PACKWORD_5(0,0,0,0,1),
	UTILS_PACKWORD_5(1,1,1,1,0)
};

const uint32_t sprite_letterT_5x5[] = {
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(0,0,1,0,0),
	UTILS_PACKWORD_5(0,0,1,0,0),
	UTILS_PACKWORD_5(0,0,1,0,0),
	UTILS_PACKWORD_5(0,0,1,0,0)
};

const uint32_t sprite_letterU_5x5[] = {
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(0,1,1,1,0)
};

const uint32_t sprite_letterV_5x5[] = {
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(0,1,0,1,0),
	UTILS_PACKWORD_5(0,0,1,0,0)
};

const uint32_t sprite_letterW_5x5[] = {
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,1,0,1),
	UTILS_PACKWORD_5(1,0,1,0,1),
	UTILS_PACKWORD_5(0,1,0,1,0)
};

const uint32_t sprite_letterX_5x5[] = {
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(0,1,0,1,0),
	UTILS_PACKWORD_5(0,0,1,0,0),
	UTILS_PACKWORD_5(0,1,0,1,0),
	UTILS_PACKWORD_5(1,0,0,0,1)
};

const uint32_t sprite_letterY_5x5[] = {
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(0,1,0,1,0),
	UTILS_PACKWORD_5(0,0,1,0,0),
	UTILS_PACKWORD_5(0,0,1,0,0),
	UTILS_PACKWORD_5(0,0,1,0,0)
};

const uint32_t sprite_letterZ_5x5[] = {
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(0,0,0,1,0),
	UTILS_PACKWORD_5(0,0,1,0,0),
	UTILS_PACKWORD_5(0,1,0,0,0),
	UTILS_PACKWORD_5(1,1,1,1,1)
};

const uint32_t sprite_number0_5x5[] = {
	UTILS_PACKWORD_5(0,1,1,1,0),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(0,1,1,1,0)
};

const uint32_t sprite_number1_5x5[] = {
	UTILS_PACKWORD_5(1,1,1,0,0),
	UTILS_PACKWORD_5(0,0,1,0,0),
	UTILS_PACKWORD_5(0,0,1,0,0),
	UTILS_PACKWORD_5(0,0,1,0,0),
	UTILS_PACKWORD_5(1,1,1,1,1)
};

const uint32_t sprite_number2_5x5[] = {
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(0,0,0,0,1),
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(1,0,0,0,0),
	UTILS_PACKWORD_5(1,1,1,1,1)
};

const uint32_t sprite_number3_5x5[] = {
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(0,0,0,0,1),
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(0,0,0,0,1),
	UTILS_PACKWORD_5(1,1,1,1,1)
};

const uint32_t sprite_number4_5x5[] = {
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(0,0,0,0,1),
	UTILS_PACKWORD_5(0,0,0,0,1)
};

const uint32_t sprite_number5_5x5[] = {
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(1,0,0,0,0),
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(0,0,0,0,1),
	UTILS_PACKWORD_5(1,1,1,1,1)
};

const uint32_t sprite_number6_5x5[] = {
	UTILS_PACKWORD_5(0,1,1,1,1),
	UTILS_PACKWORD_5(1,0,0,0,0),
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,1,1,1,1)
};

const uint32_t sprite_number7_5x5[] = {
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(0,0,0,0,1),
	UTILS_PACKWORD_5(0,0,0,0,1),
	UTILS_PACKWORD_5(0,0,0,0,1),
	UTILS_PACKWORD_5(0,0,0,0,1)
};

const uint32_t sprite_number8_5x5[] = {
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,1,1,1,1)
};

const uint32_t sprite_number9_5x5[] = {
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(1,0,0,0,1),
	UTILS_PACKWORD_5(1,1,1,1,1),
	UTILS_PACKWORD_5(0,0,0,0,1),
	UTILS_PACKWORD_5(1,1,1,1,1)
};

const uint32_t sprite_letterBLANK_5x5[] = {
	UTILS_PACKWORD_5(0,0,0,0,0),
	UTILS_PACKWORD_5(0,0,0,0,0),
	UTILS_PACKWORD_5(0,0,0,0,0),
	UTILS_PACKWORD_5(0,0,0,0,0),
	UTILS_PACKWORD_5(0,0,0,0,0)
};

// clang-format on