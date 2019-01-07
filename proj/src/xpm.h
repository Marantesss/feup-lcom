#ifndef _XPM_H
#define _XPM_H

#include "stdio.h"
#include "lcom/read_xpm.h"
#include "../images/soldier.xpm"
#include "../images/zombie_right.xpm"
#include "../images/zombie_right_middle.xpm"
#include "../images/zombie_middle.xpm"
#include "../images/zombie_left_middle.xpm"
#include "../images/zombie_left.xpm"
#include "../images/main_menu_background.xpm"
#include "../images/help_menu_background.xpm"
#include "../images/score_menu_background.xpm"
#include "../images/play_button.xpm"
#include "../images/help_button.xpm"
#include "../images/quit_button.xpm"
#include "../images/play_button_selected.xpm"
#include "../images/help_button_selected.xpm"
#include "../images/quit_button_selected.xpm"
#include "../images/main_menu_button_selected.xpm"
#include "../images/main_menu_button.xpm"
#include "../images/crosshair.xpm"
#include "../images/game_background_tile.xpm"
#include "../images/game_background_upper.xpm"
#include "../images/arcade_0.xpm"
#include "../images/arcade_1.xpm"
#include "../images/arcade_2.xpm"
#include "../images/arcade_3.xpm"
#include "../images/arcade_4.xpm"
#include "../images/arcade_5.xpm"
#include "../images/arcade_6.xpm"
#include "../images/arcade_7.xpm"
#include "../images/arcade_8.xpm"
#include "../images/arcade_9.xpm"
#include "../images/arcade_dots.xpm"
#include "../images/arcade_slash.xpm"
#include "../images/arcade_heart.xpm"
#include "../images/arcade_pause.xpm"
#include "../images/arcade_shot.xpm"
#include "minixforce.h"

/** @defgroup xpm xpm
 * @{
 *
 * Basic functions to handle XPMs
 */

/**
 * @brief Loads all XPM files necessary for the game
 */
void loadXPMs();

/**
 * @brief Loads XPM files necessary for the Main Menu
 */
void loadMainMenuXPMs();

/**
 * @brief Loads XPM files necessary for the Score Menu
 */
void loadScoreMenuXPMs();

/**
 * @brief Loads XPM files necessary for the Soldier
 */
void loadSoldierXPM();

/**
 * @brief Loads XPM files necessary for the Zombies
 */
void loadZombieXPM();

/**
 * @brief Loads XPM files necessary for the Crosshairs
 */
void loadCrosshairXPM();

/**
 * @brief Loads XPM files necessary for the Shot
 */
void loadShotXPMs();

/**
 * @brief Loads XPM files necessary for the in-game background
 */
void loadGameBackgroundXPMs();

/**
 * @brief Loads XPM files necessary for the Digits
 */
void loadDigitXPMs();

/**
 * @brief Draws an XPM at the given VRAM coordinates
 * 
 * @param xpm Pointer to XPM
 * @param x X value of the coordinate
 * @param y Y value of the coordinate
 */
void drawXPM(xpm_image_t* xpm, int x, int y);

/**
 * @brief Deletes all XPMs used in the game
 */
void deleteXPMs();

/**
 * @brief Deletes XPM passed as argument
 *
 * @param xpm Pointer to XPM
 */
void deleteXPM(xpm_image_t* xpm);

/**@}*/

#endif
