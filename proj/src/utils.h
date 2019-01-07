#ifndef _UTILS_H
#define _UTILS_H


/** @defgroup utils utils
 * @{
 *
 * Constants for MinixForce and basic auxiliary functions.
 */

/* Video Mode */
#define MINIXFORCE_GAME_MODE    0x143 /* 800x600 32 bits (8:8:8:8) */

/* Game Properties */
#define MAX_LIFES   3
/* Number of Enteties */
#define MAX_NUMBER_OF_SHOTS   3
#define NUMBER_OF_ZOMBIES     5
/* Entities Speeds */
#define SHOT_SPEED      10
#define PLAYER_SPEED    40
#define ZOMBIE_SPEED    2

/* Borders */
#define GAME_UPPER_BORDER_X    0
#define GAME_UPPER_BORDER_Y    100
#define GAME_LOWER_BORDER_X    800
#define GAME_LOWER_BORDER_Y    600

/* Digits Index */
#define NUMBER_OF_DIGITS    12
#define DIGIT_DOTS_INDEX    10
#define DIGIT_SLASH_INDEX   11

/* Zombie Sprites Index */
#define ZOMBIE_RIGHT_SPRITE         0
#define ZOMBIE_RIGHT_MIDDLE_SPRITE  1
#define ZOMBIE_MIDDLE_SPRITE        2
#define ZOMBIE_LEFT_MIDDLE_SPRITE   3
#define ZOMBIE_LEFT_SPRITE          4

/* Number of Sprites */
#define NUMBER_OF_ZOMBIE_SPRITES  5
#define NUMBER_OF_DIGIT_SPRITES   12

/* XPMs Positions */
/* Backgrounds */
#define BACKGROUND_ORIGIN_COORDS  0
/* Main Menu */
#define MAIN_PLAY_BUTTON_POSITION_X   100
#define MAIN_PLAY_BUTTON_POSITION_Y   200
#define MAIN_HELP_BUTTON_POSITION_X   100
#define MAIN_HELP_BUTTON_POSITION_Y   300
#define MAIN_QUIT_BUTTON_POSITION_X   100
#define MAIN_QUIT_BUTTON_POSITION_Y   400
/* Score Menu */
#define SCORE_MAIN_BUTTON_POSITION_X  600
#define SCORE_MAIN_BUTTON_POSITION_Y  200
#define SCORE_PLAY_BUTTON_POSITION_X  600
#define SCORE_PLAY_BUTTON_POSITION_Y  300
#define SCORE_QUIT_BUTTON_POSITION_X  600
#define SCORE_QUIT_BUTTON_POSITION_Y  400
/* Help Menu */
#define HELP_MENU_ZOMBIE_POSITION_X   400
#define HELP_MENU_ZOMBIE_POSITION_Y   400
/* RTC */
/* Date */
#define RTC_DATE_POSITION_Y             500
#define RTC_DAY_TENS_POSITION_X         290
#define RTC_DAY_ONES_POSITION_X         340
#define RTC_SLASH_1_POSITION_X          380
#define RTC_MONTH_TENS_POSITION_X       420
#define RTC_MONTH_ONES_POSITION_X       470
#define RTC_SLASH_2_POSITION_X          510
#define RTC_YEAR_THOUSANDS_POSITION_X   550
#define RTC_YEAR_HUNDREDS_POSITION_X    600
#define RTC_YEAR_TENS_POSITION_X        650
#define RTC_YEAR_ONES_POSITION_X        700
/* Clock */
#define RTC_CLOCK_POSITION_Y              400
#define RTC_CLOCK_HOURS_DIG2_POSITION_X   341
#define RTC_CLOCK_HOURS_DIG1_POSITION_X   391
#define RTC_DOTS_1_POSITION_X             428
#define RTC_CLOCK_MINS_DIG2_POSITION_X    458
#define RTC_CLOCK_MINS_DIG1_POSITION_X    508
#define RTC_DOTS_2_POSITION_X             540
#define RTC_CLOCK_SECS_DIG2_POSITION_X    570
#define RTC_CLOCK_SECS_DIG1_POSITION_X    620
/* Game Over Enemies Killed */
#define SCORE_ENEMIES_POSITION_Y        520
#define SCORE_ENEMIES_DIG3_POSITION_X   100
#define SCORE_ENEMIES_DIG2_POSITION_X   150
#define SCORE_ENEMIES_DIG1_POSITION_X   200
/* Game Over Timer */
#define SCORE_MINUTES_DIG2_POSITION_X   95
#define SCORE_MINUTES_DIG2_POSITION_Y   360
#define SCORE_MINUTES_DIG1_POSITION_X   145
#define SCORE_MINUTES_DIG1_POSITION_Y   360
#define SCORE_DOTS_POSITION_X   175
#define SCORE_DOTS_POSITION_Y   360
#define SCORE_SECONDS_DIG2_POSITION_X   205
#define SCORE_SECONDS_DIG2_POSITION_Y   360
#define SCORE_SECONDS_DIG1_POSITION_X   255
#define SCORE_SECONDS_DIG1_POSITION_Y   360
/* Game Over Score */
#define SCORE_TENTHOUSANDS_POSITION_X  90
#define SCORE_TENTHOUSANDS_POSITION_Y  200
#define SCORE_THOUSANDS_POSITION_X     140
#define SCORE_THOUSANDS_POSITION_Y     200
#define SCORE_HUNDREDS_POSITION_X      190
#define SCORE_HUNDREDS_POSITION_Y      200
#define SCORE_TENS_POSITION_X          240
#define SCORE_TENS_POSITION_Y          200
#define SCORE_ONES_POSITION_X          290
#define SCORE_ONES_POSITION_Y          200
/* Pause */
#define PAUSED_POSITION_X  183
#define PAUSED_POSITION_Y  264
/* Game Timer */
#define GAME_MINUTES_DIG2_POSITION_X   558
#define GAME_MINUTES_DIG2_POSITION_Y   25
#define GAME_MINUTES_DIG1_POSITION_X   608
#define GAME_MINUTES_DIG1_POSITION_Y   25
#define GAME_DOTS_POSITION_X   640
#define GAME_DOTS_POSITION_Y   25
#define GAME_SECONDS_DIG2_POSITION_X   670
#define GAME_SECONDS_DIG2_POSITION_Y   25
#define GAME_SECONDS_DIG1_POSITION_X   720
#define GAME_SECONDS_DIG1_POSITION_Y   25
/* Game Score */
#define GAME_TENTHOUSANDS_POSITION_X  275
#define GAME_TENTHOUSANDS_POSITION_Y  25
#define GAME_THOUSANDS_POSITION_X     325
#define GAME_THOUSANDS_POSITION_Y     25
#define GAME_HUNDREDS_POSITION_X      375
#define GAME_HUNDREDS_POSITION_Y      25
#define GAME_TENS_POSITION_X          425
#define GAME_TENS_POSITION_Y          25
#define GAME_ONES_POSITION_X          475
#define GAME_ONES_POSITION_Y          25
/* Crosshair */
#define CROSSHAIR_INITIAL_POSITION_X  260
#define CROSSHAIR_INITIAL_POSITION_Y  360
/* Hearts */
#define HEARTS_POSITION_X  30
#define HEARTS_POSITION_Y  26
#define HEARTS_GAP_BETWEEN  60
/* Soldier */
#define PLAYER_INITIAL_POSITION_X  0
#define PLAYER_INITIAL_POSITION_Y  314
/*Cout Down */
#define COUNT_INITIAL_POSITION_X   380
#define COUNT_INITIAL_POSITION_Y   300
/**
 * @brief Returns a random number between two limits passed as argument.
 *
 * @param lowerBound lower limit of the number generated
 * @param higherBound upper limit of the number generated
 *
 * @return a random number between lower bound and higher bound
 */
int generateRandomCoordinate(int lowerBound, int upperBound);

/**@}*/

#endif /* _UTILS_H */
