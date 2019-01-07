#ifndef _INTERRUPTS_H_
#define _INTERRUPTS_H_

#include "timer.h"
#include "minixforce.h"
#include "states.h"
#include "keyboard.h"
#include "movement.h"
#include "mouse.h"
#include "i8042.h"

/** @defgroup interrupts interrupts
 * @{
 * 
 *  Subscribes and unsubscribes all interrupts. \n
 *  Removes all information from the buffer. \n
 *  Sends the event or the new status to functions in state.h. \n
 */

/**
 * @brief Subscribes all interrupts need during all the execution of the program.
 * Such as the timer, keyboard, mouse and rtc.
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int subscribes();

/**
 * @brief unsubscribes all interrupts need during all the execution of the program.
 * Such as the timer, keyboard, mouse and rtc.
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int unsubscribes();

/**
 * @brief 
 * Base on the status of the game, calls the corresponding interrupt handler. \n
 * Which means, if the game is the MAIN_MENU status it calls main_menu_IH(),
 * if it in the help menu or in pause, it calls help_pause_IH().
 * If we are playing the game, it calls de IHgame(),
 * and if we are in the score menu, it calls IHend().
 */
void interruptHandler();

/**
 * @brief 
 * Is the interrupt handler for the score menu.
 * It detets the arrows up and down.
 * If we prees enter we go to the state selected.
 * It removes mouse information from the buffer.
 */
void IHend();

/**
 * @brief 
 * Is the interrupt handler for the score menu. \n
 * It uses the timer only. \n
 * It removes keyboard and mouse information from the buffer. \n
 * The count down is faster than 1 minute and slower than 1 second.
 */
void IHcount();

/**
 * @brief 
 * Is the interrupt handler for the main menu.
 * It detets the arrows up and down.
 * If we prees enter we go to the state selected.
 * It removes mouse information from the buffer.
 * It deals with timer. AS timer is interrupting, the rtc is updated.
 */
void main_menu_IH();

/**
 * @brief
 * Is the interrupt handler for the game. \n
 * It detets the keys W,S,A,D for movement. \n
 * If we press space it pauses the game. \n
 * If we press ESC it leaves the game. \n
 * The movement of the mouse is the movement of the crosshair. \n
 * If we press the right buttom it fires. \n
 * The timer is also use to increment the time alive ov the struct minis force.
 */
void IHgame();

/**
 * @brief 
 * if we are in the help menu and press esc, leave to main. \n
 * if we are in pause and press break, continue game \n
 * it removes mouse information from the buffer. \n
 * It stops the game we util the rigth key is press. \n
 * In pause menu, stays in the loop until "space is press".
 */
void help_pause_IH();


#endif /* _INTERRUPTS_H_ */
