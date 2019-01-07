#ifndef _STATES_H_
#define _STATES_H_

/** @defgroup states states
 * @{
 * The file keeps the states of the game, mouse, player, main and score. \n
 * It also was fuctions to update the state base on the event.
 */

/**
 * @brief 
 * enumeration with all states of main menu. \n
 * Each state matches the selected option.
 */
typedef enum {

    MPLAY,          /** @brief Starts plaing the game.*/
    MHELP,          /** @brief opens the help menu*/
    MEXIT           /** @brief leaves the program */

} stateMAIN;

/**
 * @brief 
 * Enumeration with all the event of main menu.
 */
typedef enum {

    KUP,            /** @brief Arrow up key was press */
    KDOWN,          /** @brief Arrow down key was press  */
    ENTER           /** @brief Enter key was press */

} menu_event_t;


/**
 * @brief 
 * All possible states of the game.
 */
typedef enum {
	MAIN_MENU,  
    HELP_MENU,
    COUNT_DOWN,
    GAME,
    PAUSE_MENU, 
    SCORE_MENU,
    END_MENU

} stateGAME;

/**
 * @brief 
 *  All possible events of the game. Wich event changes the a state.
 * It can be a game state or not.
 */
typedef enum {
    MAIN,
    COUNT,
	SPLAYER, 
    HELP, 
    SCORE,
    PAUSE,
    EXIT

} game_event_t;

/**
 * @brief 
 *  Changes with the moviment of player.\n
 *  Handler should put the state in DEFAULT.
 */
typedef enum {
    FRONT,
    BACK,
    PUP,
    PDOWN,
    DEFAULT
} statePLAYER ;

/**
 * @brief 
 * For event of fire, which is the press of left buttom during the game.
 */
typedef enum {
	FIRE,
    DEF
} stateMOUSE;

/**
 * @brief 
 * The state is the option selected in the main menu.
 */
typedef enum {
    B_TO_MAIN,
    RESTART,
    LEAVE
} stateSCORE;

/**
 * @brief 
 * Changes the player state.
 * @param new player state.
 */
void updatePlayerState(statePLAYER newState);


/**
 * @brief 
 * Changes the mouse state.
 * @param  new mouse state.
 */
void updateMouseState(stateMOUSE newState);

/**
 * @brief 
 * When an arrow is press up or down, this fuction is call. \n
 * Because there is only 3 option, when a change is not possible,
 * a state is not changed with an event. \n
 * So, this function is always call, but not always something diferent appens
 * 
 * @param event that happen in Main state
 */
void updateMainState(menu_event_t Nevent);

/**
 * @brief 
 * When an arrow is press up or down, this fuction is call. \n
 * Because there is only 3 option, when a change is not possible,
 * a state is not changed with an event. \n
 * So, this function is always call, but not always something diferent appens
 * @param event that happen in Score state
 */
void updateScoreState(menu_event_t Eevent);
/**
 * @brief 
 *  Depending on the atual state of the game and on the event (pass as perameter), this function updates 
 * the game to the new state. 
 * @param event that happen during the execution of the program
 */
void updateGameState(game_event_t Gevent);

/**
 * @brief 
 * This function is to make the code cleaner. \n
 * 
 * @return the states that is selected in the main menu.
 */
stateMAIN getStateMain();

/**
 * @brief 
 * This function is to make the code cleaner. \n
 * 
 * @return the states  of the game.
 */
stateGAME getStateGame();

/**
 * @brief 
 * This function is to make the code cleaner. \n
 * 
 * @return the states of the player. The states that handler this state must put it in default.
 */
statePLAYER getStatePlayer();

/**
 * @brief 
 * This function is to make the code cleaner. \n
 * It is used to detect when a shot is fire.
 * 
 * @return the states of the mouse.
 */
stateMOUSE getStateMouse();

/**
 * @brief 
 * This function is to make the code cleaner. \n
 * @return the states that is selected in the main menu.
 */
stateSCORE getStateScore();

/**@}*/

#endif      /* STATES_H */
