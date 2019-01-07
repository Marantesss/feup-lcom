#ifndef _MINIXFORCE_H
#define _MINIXFORCE_H

#include <lcom/lcf.h>
#include "entities.h"
#include "video_gr.h"
#include "xpm.h"
#include "states.h"
#include "rtc.h"
#include "interrupts.h"
#include "utils.h"

/** @defgroup minixforce minixforce
 * @{
 *
 * Game main struct and main functions
 */

typedef struct
{
	// INTERRUPT INDEX OG THE IPC
	unsigned int lifes; /**< @brief Number of lifes the player has */
	unsigned int enemiesKilled; /**< @brief Number of enemies killed by the player */
	unsigned int score; /**< @brief In-game score achieved */

	//Atual states
	stateGAME MFstateGame;
	stateMAIN MFstateMain;
	statePLAYER MFstatePlayer;
	stateMOUSE MFstateMouse;
	stateSCORE MFstateScore;

	//struct with hours and date
	rtc_time_t* real_time;

	unsigned int time_alive; /**< @brief Time the player is alive */
	int countDown; /**< @brief Count Down timer to start a new game */
	int time_ticket; /**< @brief 1 if some event happened, 0 otherwise. Used to update VRAM */

	// false when stop execution
	bool endEnd; /**< @brief  */

	// Entities
	MainMenu* main_menu; /**< @brief coordinates of upper left point of sprite */
	ScoreMenu* score_menu; /**< @brief coordinates of upper left point of sprite */

	Player* soldier; /**< @brief Pointer to soldier */
	Enemy* zombies[NUMBER_OF_ZOMBIES]; /**< @brief Pointer array to zombies */
	Shot* shots[MAX_NUMBER_OF_SHOTS]; /**< @brief Pointer array to shots */
	Crosshair* crosshair; /**< @brief Pointer to crosshair */
	xpm_image_t paused; /**< @brief Image of PAUSED */
	xpm_image_t heart; /**< @brief Image of HEART */
	xpm_image_t tileBackground; /**< @brief Image of game background */
	xpm_image_t upperBackground; /**< @brief Image of game upper background */
	xpm_image_t digits[NUMBER_OF_DIGITS]; /**< @brief Image array of digits */

} MinixForce;

/**
 * @brief It allocats memory for the essencial stucts Minixforce. \n
 * Subscribe all interrupts. \n
 * calls a function that initializes all values of the stuct.
 * 
 * @return a pointer to the game initialized
 */
MinixForce * initMinixForce();

/**
 * @brief Initializes all values of the game.
 */
void initValues();

/**
 * @brief If it does find the game being play, it initiats one.
 * 
 * @return a pointer to the stuct of the game being played
 */
MinixForce *getGame();


/**
 * @brief it restarts all values of the variables to their initial values. \n
 */
void restartMinixForce();

/**
 * @brief Clears all memory being allocated during the execution of the game.\n
 * Also unsubscribes the interrupts.
 */
void endMinixForce();

/**@}*/

#endif /* _MINIXFORCE_H */
