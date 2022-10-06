#include "Sprites.h"

#include <cassert>

#include "Sprite.h"
#include "resources/sprites.h"

// Constructor - construct all sprites
Sprites::Sprites() {
  // Saucer
  ufo = new Sprite(sprite_ufo_16x7, SPRITES_16X7_ROWS, SPRITES_16X7_COLS);

  // Alien Explosion
  explosion = new Sprite(sprite_alien_explosion_12x10, SPRITES_12X10_ROWS,
                         SPRITES_12X10_COLS);

  // Aliens
  aliens[SPRITE_ALIEN_TOP_IN] = new Sprite(
      sprite_alien_top_in_12x8, SPRITES_12X8_ROWS, SPRITES_12X8_COLS);
  aliens[SPRITE_ALIEN_TOP_OUT] = new Sprite(
      sprite_alien_top_out_12x8, SPRITES_12X8_ROWS, SPRITES_12X8_COLS);
  aliens[SPRITE_ALIEN_MID_IN] = new Sprite(
      sprite_alien_middle_in_12x8, SPRITES_12X8_ROWS, SPRITES_12X8_COLS);
  aliens[SPRITE_ALIEN_MID_OUT] = new Sprite(
      sprite_alien_middle_out_12x8, SPRITES_12X8_ROWS, SPRITES_12X8_COLS);
  aliens[SPRITE_ALIEN_BOT_IN] = new Sprite(
      sprite_alien_bottom_in_12x8, SPRITES_12X8_ROWS, SPRITES_12X8_COLS);
  aliens[SPRITE_ALIEN_BOT_OUT] = new Sprite(
      sprite_alien_bottom_out_12x8, SPRITES_12X8_ROWS, SPRITES_12X8_COLS);

  // Tanks
  tanks[SPRITE_TANK] =
      new Sprite(sprite_tank_15x8, SPRITES_15X8_ROWS, SPRITES_15X8_COLS);
  tanks[SPRITE_TANK_EXPLOSION1] = new Sprite(
      sprite_tank_explosion1_15x8, SPRITES_15X8_ROWS, SPRITES_15X8_COLS);
  tanks[SPRITE_TANK_EXPLOSION2] = new Sprite(
      sprite_tank_explosion2_15x8, SPRITES_15X8_ROWS, SPRITES_15X8_COLS);

  // Bunker
  bunker =
      new Sprite(sprite_bunker_24x18, SPRITES_24X18_ROWS, SPRITES_24X18_COLS);

  // Bunker Damage
  bunkerDmg.push_back(
      new Sprite(sprite_bunkerDamage0_6x6, SPRITES_6X6_ROWS, SPRITES_6X6_COLS));
  bunkerDmg.push_back(
      new Sprite(sprite_bunkerDamage1_6x6, SPRITES_6X6_ROWS, SPRITES_6X6_COLS));
  bunkerDmg.push_back(
      new Sprite(sprite_bunkerDamage2_6x6, SPRITES_6X6_ROWS, SPRITES_6X6_COLS));
  bunkerDmg.push_back(
      new Sprite(sprite_bunkerDamage3_6x6, SPRITES_6X6_ROWS, SPRITES_6X6_COLS));
  bunkerDmg.push_back(
      new Sprite(sprite_bunkerDamage4_6x6, SPRITES_6X6_ROWS, SPRITES_6X6_COLS));

  // Bullet
  bullets[SPRITE_BULLET_TANK] =
      (new Sprite(sprite_tankbullet_1x5, SPRITES_1X5_ROWS, SPRITES_1X5_COLS));
  bullets[SPRITE_BULLET_ALIEN1_DOWN] = (new Sprite(
      sprite_alienbullet1_down_3x5, SPRITES_3X5_ROWS, SPRITES_3X5_COLS));
  bullets[SPRITE_BULLET_ALIEN1_UP] = (new Sprite(
      sprite_alienbullet1_up_3x5, SPRITES_3X5_ROWS, SPRITES_3X5_COLS));
  bullets[SPRITE_BULLET_ALIEN2_DOWN] = (new Sprite(
      sprite_alienbullet2_down_3x5, SPRITES_3X5_ROWS, SPRITES_3X5_COLS));
  bullets[SPRITE_BULLET_ALIEN2_UP] = (new Sprite(
      sprite_alienbullet2_up_3x5, SPRITES_3X5_ROWS, SPRITES_3X5_COLS));

  // Letters
  chars['A'] =
      new Sprite(sprite_letterA_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['B'] =
      new Sprite(sprite_letterB_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['C'] =
      new Sprite(sprite_letterC_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['D'] =
      new Sprite(sprite_letterD_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['E'] =
      new Sprite(sprite_letterE_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['F'] =
      new Sprite(sprite_letterF_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['G'] =
      new Sprite(sprite_letterG_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['H'] =
      new Sprite(sprite_letterH_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['I'] =
      new Sprite(sprite_letterI_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['J'] =
      new Sprite(sprite_letterJ_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['K'] =
      new Sprite(sprite_letterK_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['L'] =
      new Sprite(sprite_letterL_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['M'] =
      new Sprite(sprite_letterM_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['N'] =
      new Sprite(sprite_letterN_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['O'] =
      new Sprite(sprite_letterO_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['P'] =
      new Sprite(sprite_letterP_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['Q'] =
      new Sprite(sprite_letterQ_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['R'] =
      new Sprite(sprite_letterR_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['S'] =
      new Sprite(sprite_letterS_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['T'] =
      new Sprite(sprite_letterT_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['U'] =
      new Sprite(sprite_letterU_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['V'] =
      new Sprite(sprite_letterV_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['W'] =
      new Sprite(sprite_letterW_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['X'] =
      new Sprite(sprite_letterX_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['Y'] =
      new Sprite(sprite_letterY_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['Z'] =
      new Sprite(sprite_letterZ_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars[' '] =
      new Sprite(sprite_letterBLANK_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);

  chars['0'] =
      new Sprite(sprite_number0_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['1'] =
      new Sprite(sprite_number1_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['2'] =
      new Sprite(sprite_number2_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['3'] =
      new Sprite(sprite_number3_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['4'] =
      new Sprite(sprite_number4_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['5'] =
      new Sprite(sprite_number5_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['6'] =
      new Sprite(sprite_number6_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['7'] =
      new Sprite(sprite_number7_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['8'] =
      new Sprite(sprite_number8_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
  chars['9'] =
      new Sprite(sprite_number9_5x5, SPRITES_5X5_ROWS, SPRITES_5X5_COLS);
}

// destructor for all sprites
Sprites::~Sprites() {
  for (auto i : chars)
    delete i.second;
  for (auto i : aliens)
    delete i.second;
  for (auto i : tanks)
    delete i.second;
  for (auto i : bullets)
    delete i.second;
  for (auto i : bunkerDmg)
    delete i;
  delete ufo;
  delete explosion;
  delete bunker;
}

// Returns the sprite for a given character
Sprite *Sprites::getChar(char letter) {
  if (chars.count(letter) == 0)
    return NULL;
  return chars[letter];
}

// Returns the sprite for a given alien type
Sprite *Sprites::getAlien(sprite_alien_type_t alien_type) {
  if (aliens.count(alien_type) == 0)
    return NULL;
  return aliens[alien_type];
}

// Returns a tank sprite (tank or explosion)
Sprite *Sprites::getTank(sprite_tank_type_t tank_type) {
  if (tanks.count(tank_type) == 0)
    return NULL;
  return tanks[tank_type];
}

// Returns a bullet sprite, given the type
Sprite *Sprites::getBullet(sprite_bullet_type_t bullet_type) {
  assert(bullets.count(bullet_type) != 0);
  // return NULL;
  return bullets[bullet_type];
}

// Returns a bunker damage pattern, given a damage level
Sprite *Sprites::getBunkerDmg(uint8_t dmgLevel) {
  assert(dmgLevel < bunkerDmg.size());
  return bunkerDmg[dmgLevel];
}
