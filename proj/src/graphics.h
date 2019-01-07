#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "lcom/lcf.h"
#include "states.h"
#include "minixforce.h"
#include "videomacros.h"
#include "video_gr.h"

/** @defgroup graphics graphics
 * @{
 *
 * Basic functions draw the various entities
 */

/** 
 * @brief Calls draw functions depending on the game state
 */
void drawMinixForce();

/**
 * @brief Draws Main Menu XPMs depending on Main Menu states
 */
void drawMainMenu();

/**
 * @brief Draws Help Menu
 */
void drawHelpMenu();

/**
 * @brief Draws in-game XPMs
 */
void drawGame();

/**
 * @brief Draws PAUSE XPM on screen when game is paused
 */
void drawPauseMenu();

/**
 * @brief Draws in-game board and upper background
 */
void drawGameBackground();

/**
 * @brief Draws soldier on screen
 */
void drawSoldier();

/**
 * @brief Draws crosshair on screen
 */
void drawCrosshair();

/**
 * @brief Draws all shots on screen
 */
void drawShot();

/**
 * @brief Draws in-game timer on upper background
 */
void drawGameTimer();

/**
 * @brief Draws hearts equal to number of lifes the player has
 */
void drawGameLifes();

/**
 * @brief Draws game score on screen
 * Also draws count down on screen before starting a new game, if state in COUNT_DOWN
 */
void drawGameScore();

/**
 * @brief Draws game score when the game is over
 */
void drawScoreMenu();

/**
 * @brief Draws number of enemies killed when the game is over
 */
void drawEnemiesKilled();

/**
 * @brief Draws enemies on screen
 */
void drawEnemies();

/**@}*/

#endif      /* _GRAPHICS_H */
