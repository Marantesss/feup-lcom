#ifndef _PROJECTO_H_
#define _PROJECTO_H_

#include "game.h"
#include "minixforce.h"

/** @defgroup proj proj
 * @{
 * 
 * Main function to start the game
 */

/** 
 * @brief 
 * It only calls the function play. \n
 * If we can not subscribe some controler or init video game mode, the execution stops.
 * @return Return 0 upon success and non-zero otherwise
 */
int (proj_main_loop)();

/**@}*/

#endif 
