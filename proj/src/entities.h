
#ifndef _ENTITIES_H
#define _ENTITIES_H

#include "lcom/lcf.h"
#include "collision.h"
#include "utils.h"

/** @defgroup entities entities
 * @{
 *
 * Structs that represent sprites and functions for memory allocation and sprite initialization
 */

typedef struct {
	uint16_t x;						/**< @brief X coordinate of Button Sprite */
	uint16_t y;						/**< @brief Y coordinate of Button Sprite */
	xpm_image_t normal;		/**< @brief Image of button */
	xpm_image_t selected;	/**< @brief Image of selected button */
} Button;

typedef struct {	
	Button* playButton;					/**< @brief Pointer to Play Button */
	Button* helpButton;					/**< @brief Pointer to Help Button */
	Button* quitButton;					/**< @brief Pointer to Quit Button */
	xpm_image_t menuBackground;	/**< @brief Image of Main Menu Background */
	xpm_image_t helpBackground;	/**< @brief Image of Help Menu */
} MainMenu;

typedef struct {	
	Button* backMainButton; 		/**< @brief Pointer to Back Button */
	Button* restartButton;			/**< @brief Pointer to Restart Button */
	Button* quitButton;					/**< @brief Pointer to Quit Button */
	xpm_image_t menuBackground; /**< @brief Image of Score Menu's Background */
} ScoreMenu;

typedef struct {
	uint16_t x;							/**< @brief X coordinate of Button Sprite */
	uint16_t y;							/**< @brief Y coordinate of Button Sprite */	CollisionArea* body;		/**< @brief Pointer to Player Sprite's Collision Area */
	xpm_image_t soldierFwd;	/**< @brief Image of Soldier */
} Player;

typedef struct {
	uint16_t x;				/**< @brief X coordinate of Button Sprite */
	uint16_t y;				/**< @brief Y coordinate of Button Sprite */
	xpm_image_t aim;	/**< @brief Image of Crosshair */
} Crosshair;

typedef struct {
	uint16_t xSpeed, ySpeed;	/**< @brief Speed of Y and X dimensions */
	uint16_t x;								/**< @brief X coordinate of Button Sprite */
	uint16_t y;								/**< @brief Y coordinate of Button Sprite */
	bool useBullet;						/**< @brief Flag to draw bullet or not */
	CollisionArea* body;			/**< @brief Pointer to Shot's Sprite Collision Area */
	xpm_image_t bullet;				/**< @brief Image of Shot */
} Shot;

typedef struct {
	uint16_t x;						/**< @brief X coordinate of Button Sprite */
	uint16_t y;						/**< @brief Y coordinate of Button Sprite */ 	CollisionArea* body;	/**< @brief Pointer to Enemy's Collision Area */
	xpm_image_t zombie_sprites[NUMBER_OF_ZOMBIE_SPRITES]; /**< @brief Image array of Zombies */
} Enemy;

/**
 * @brief Allocates memory for all entities in the game
 */
void createEntities();

/**
 * @brief Initialize Main Menu's XPMs' positions
 */
void initMainMenu();

/**
 * @brief Initialize Score Menu's XPMs' positions
 */
void initScoreMenu();

/**
 * @brief Initialize Soldier's XPM position
 * And creates a CollisionArea
 */
void initSoldier();

/**
 * @brief Initialize Crosshair's XPM position
 */
void initCrosshair();

/**
 * @brief Initialize enemies' XPMs' positions
 * And creates CollisionAreas
 */
void initEnemies();

/**
 * @brief Initialize shots' XPMs' positions
 * And creates CollisionAreas
 */
void initShots();

/**@}*/

#endif
