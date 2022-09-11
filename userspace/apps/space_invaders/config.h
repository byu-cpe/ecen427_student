#ifndef CONFIG
#define CONFIG

#include "resources/sprites.h"

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// Tank configuration /////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// How often to move the tank
#define TANK_MOVE_DELAY_SECONDS 0.02

// How far the tank moves (pixels)
#define TANK_MOVE_X_DISTANCE 3

// Tank size, position, color
#define TANK_SIZE 2
#define TANK_HEIGHT (SPRITES_15X8_ROWS * TANK_SIZE)
#define TANK_Y (GRAPHICS_HEIGHT - TANK_HEIGHT * 1.1)
#define TANK_COLOR Colors::GREEN

// Duration of tank death animation
#define TANK_DEATH_DURATION_SECONDS 1.5

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// Alien configuration ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Number of aliens
#define ALIENS_ROWS 5
#define ALIENS_COLS 11

// Alien size, color, spacing and margin to screen edge
#define ALIENS_SIZE 2
#define ALIENS_COLOR Colors::WHITE
#define ALIENS_SPACE_GAP_X 10
#define ALIENS_SPACE_GAP_Y 10
#define ALIENS_LEFT_RIGHT_MARGIN 30

// Alien movement behavior
#define ALIENS_MOVE_DELAY_SECONDS 0.5
#define ALIENS_MOVE_X_DISTANCE 5
#define ALIENS_MOVE_Y_DISTANCE 10

// How often alien bullets are fired
#define ALIENS_BULLET_MIN_WAIT_SECONDS 0.1
#define ALIENS_BULLET_MAX_WAIT_SECONDS 1

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// UFO configuration //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// UFO size, position, color
#define UFO_SIZE 2
#define UFO_Y 50
#define UFO_COLOR Colors::RED

// UFO movement behavior
#define UFO_MOVE_DELAY_SECONDS 0.05
#define UFO_MOVE_X_DISTANCE 5
#define UFO_HIDE_DELAY_MIN_SECONDS 5
#define UFO_HIDE_DELAY_MAX_SECONDS 15

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// Bullet configuration ///////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Bullet size, color
#define BULLET_SIZE 2
#define BULLET_COLOR Colors::WHITE

// Bullet movement behavior
#define BULLET_MOVE_DELAY_SECONDS 0.02
#define BULLET_MOVE_Y_DISTANCE_PLAYER 5
#define BULLET_MOVE_Y_DISTANCE_ENEMY 2

// Maximum number of alien bullets on the screen at one time
// (there can only be one player bullet)
#define BULLET_ENEMY_MAX_COUNT 4

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// Bunker configuration ///////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Number of bunkers
#define BUNKER_COUNT 4

// Bunker size, position, color
#define BUNKER_SIZE 2
#define BUNKER_Y (GRAPHICS_HEIGHT * 0.8)
#define BUNKER_COLOR Colors::GREEN

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// Lives configuration ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Number of lives the player gets
#define LIVES_AT_START 3
#define LIVES_MAX 4

// Positioning, size and spacing of lives shown in top-right corner
#define LIVES_X (GRAPHICS_WIDTH * 0.65)
#define LIVES_X_PAD 5
#define LIVES_Y 10
#define LIVES_TEXT_SIZE 2

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// Score configuration ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Score size and positioning shown in top-left corner
#define SCORE_X_MARGIN 10
#define SCORE_Y_MARGIN 10
#define SCORE_SIZE 2
#define SCORE_DIGITS 5

// Points for different aliens
#define SCORE_TOP_ALIEN 30
#define SCORE_MID_ALIEN 20
#define SCORE_BOT_ALIEN 10
#define SCORE_SPACESHIP_MIN 50
#define SCORE_SPACESHIP_MAX 300

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// High Scores configuration //////////////////////
////////////////////////////////////////////////////////////////////////////////

// High scores screen text size, and blink rate
#define HIGH_SCORES_TITLE_TEXT_SIZE 6
#define HIGH_SCORES_TEXT_SIZE 2
#define HIGH_SCORES_ENTRY_BLINK_RATE_SECONDS 0.5

// Number of characters that can be input for high score entry
#define HIGH_SCORES_NUM_CHARS 3

// Maximum number of high score entries
#define HIGH_SCORES_MAX_ENTRIES 8

#endif /* CONFIG */
