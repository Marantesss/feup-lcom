#ifndef _MOVEMENT_H
#define _MOVEMENT_H

#include "minixforce.h"
#include "interrupts.h"
#include "rtc.h"
#include "util.h"
#include <math.h>

/** @defgroup movement movement
 * @{
 *
 * Functions to update game states and enteties position on screen
 */

/**
 * @brief If player dies, puts state game in score menu. \n
 * Updates the state of the game. \n
 * Calls rtc if states is the main menu, where it is used. \n
 * During the game it handles events, updating the positions of entities.
 */
void updateMinixForce();

/**
 * @brief Updates evething on the game, based on the events appended.
 */
void events();

/**
 * @brief Score is the sum of the time alive plus the bonus of enemies killed.
 */
void updateScore();

/**
 * @brief Updates the position of the soldier based on the status of the keyboard.
 */
void updateSoldier();

/**
 * @brief Updates player position by decrementing its coordinates Y value
 */
void moveSoldierUp();

/**
 * @brief Updates player position by incrementing its coordinates Y value
 */
void moveSoldierDown();

/**
 * @brief Updates player position by decrementing its coordinates X value
 */
void moveSoldierBack();

/**
 * @brief Updates player's position by incrementing its coordinates X value
 */
void moveSoldierFront();

/**
 * @brief Resets player's coordinates to the starting position
 */
void resetSoldierPosition();

/**
 * @brief Resets crosshair's coordinates to the starting position
 */
void resetCrosshairPosition();

/**
 * @brief Updates all zombies' postions, based on the events appended
 * Zombies' speed is incresead every 30 seconds
 */
void updateZombiesPositions();

/**
 * @brief Resets all zombies' coordinates to the starting position 
 */
void resetZombiesPositions();

/**
 * @brief recalculates a zombie's position passed as argument
 * 
 * @param zombie pointer to the zombie that is going to be updated
 */
void recalculateZombiePosition(Enemy* zombie);

/**
 * @brief Updates all shots' position
 */
void updateShots();

/**
 * @brief Updates a shot's position passed as argument
 * 
 * @param bullet pointer to the shot that is going to be updated
 */
void updateShot(Shot* bullet);

/**
 * @brief Calculates a shot's speed in X and Y fields acording to player's and crosshair's position
 */
void calculateShotSpeed(Shot* bullet);

/**
 * @brief Checks for in-game collisions
 */
void checkCollisions();

/**
 * @brief Checks for in-game collisions between shots and zombies
 */
void checkShotCollisions();

/**
 * @brief Checks for in-game collisions between player and zombies 
 */
void checkPlayerCollisions();

/**
 * @brief Updates countdown timer when starting a new game
 */
void updateCount();

/**@}*/

#endif /* _MOVEMENT_H */
