#ifndef _GAME_H_
#define _GAME_H_

#include "minixforce.h"

/** @defgroup 
 * @{
 * Functions of upper level. \n
 * The first function calls the other 3 functions declared where, that start, play and end of the game.
 */

/**
 * @brief 
 * Calls fuctions that contain the tree basic steps of the game. \n
 * That means it that starts the game, plays it and ends it.
 * This function calls the other 3 functions declared in where.
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int play();

/**
 * @brief
 * Starts the game, that means it init the video mode and
 * calls a function that inits the game properties.
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int stGame();

/**
 * @brief
 * 
 * Loops through the game. \n
 * It stops when the game ends. \n
 * It calls the interrupt Handler. Base on the interrupt, the state of something is change. \n
 * The Update changes the struct base on the state changed. \n
 * And finaly it draws the updated image of the game.
 */
void gamePlay();

/**
 * @brief
 * Calls a function that eliminate the memory allocated. \n
 * leaves video mode.
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int endGame();

#endif      /* GAME_H */
