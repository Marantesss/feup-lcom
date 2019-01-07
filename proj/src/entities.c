#include "entities.h"
#include "minixforce.h"
#include "utils.h"
#include "movement.h"

void createEntities() {
	MinixForce* game = getGame();

	/* Main Menu & Help Menu */
	game->main_menu = (MainMenu*) malloc(sizeof(MainMenu));
	game->main_menu->playButton = (Button*) malloc(sizeof(Button));
	game->main_menu->helpButton = (Button*) malloc(sizeof(Button));
	game->main_menu->quitButton = (Button*) malloc(sizeof(Button));

	/* Score Menu */
	game->score_menu = (ScoreMenu*) malloc(sizeof(ScoreMenu));
	game->score_menu->backMainButton = (Button*) malloc(sizeof(Button));
	game->score_menu->restartButton = (Button*) malloc(sizeof(Button));
	game->score_menu->quitButton = (Button*) malloc(sizeof(Button));
	
	/* Soldier */
	game->soldier = (Player*) malloc(sizeof(Player));

	/* Crosshair */
	game->crosshair = (Crosshair*) malloc(sizeof(Crosshair));

	/* Zombies */
	for (int i = 0; i < NUMBER_OF_ZOMBIES; i++) {
		game->zombies[i] = (Enemy*) malloc(sizeof(Enemy));
	}
	/* Bullets */
	for (int i = 0; i < MAX_NUMBER_OF_SHOTS; i++) {
		game->shots[i] = (Shot*) malloc(sizeof(Shot));
		game->shots[i]->useBullet = false;
	}
}

void initMainMenu() {
  MinixForce* game = getGame();

	game->main_menu->playButton->x = MAIN_PLAY_BUTTON_POSITION_X;
	game->main_menu->playButton->y = MAIN_PLAY_BUTTON_POSITION_Y;

	game->main_menu->helpButton->x = MAIN_HELP_BUTTON_POSITION_X;
	game->main_menu->helpButton->y = MAIN_HELP_BUTTON_POSITION_Y;

	game->main_menu->quitButton->x = MAIN_QUIT_BUTTON_POSITION_X;
	game->main_menu->quitButton->y = MAIN_QUIT_BUTTON_POSITION_Y;
}

void initScoreMenu() {
  MinixForce* game = getGame();

	game->score_menu->backMainButton->x = SCORE_MAIN_BUTTON_POSITION_X;
	game->score_menu->backMainButton->y = SCORE_MAIN_BUTTON_POSITION_Y;

	game->score_menu->restartButton->x = SCORE_PLAY_BUTTON_POSITION_X;
	game->score_menu->restartButton->y = SCORE_PLAY_BUTTON_POSITION_Y;

	game->score_menu->quitButton->x = SCORE_QUIT_BUTTON_POSITION_X;
	game->score_menu->quitButton->y = SCORE_QUIT_BUTTON_POSITION_Y;
}

void initSoldier() {
  MinixForce* game = getGame();

	int soldierWidth = game->soldier->soldierFwd.width;
	int soldierHeight = game->soldier->soldierFwd.height;

	game->soldier->x = PLAYER_INITIAL_POSITION_X; 
	game->soldier->y = PLAYER_INITIAL_POSITION_Y;

	game->soldier->body = newCollisionArea(game->soldier->x, game->soldier->y, game->soldier->x + soldierWidth, game->soldier->y + soldierHeight);
}

void initCrosshair() {
  MinixForce* game = getGame();

	game->crosshair->x = CROSSHAIR_INITIAL_POSITION_X;
	game->crosshair->y = CROSSHAIR_INITIAL_POSITION_Y;
}

void initEnemies() {
	MinixForce* game = getGame();

	int zombieWidth = game->zombies[0]->zombie_sprites[ZOMBIE_MIDDLE_SPRITE].width;
	int zombieHeight = game->zombies[0]->zombie_sprites[ZOMBIE_MIDDLE_SPRITE].height;
	
	for (int i = 0; i < NUMBER_OF_ZOMBIES; i++) {
		game->zombies[i]->x = GAME_LOWER_BORDER_X + generateRandomCoordinate(GAME_UPPER_BORDER_X, GAME_LOWER_BORDER_X);
		game->zombies[i]->y = generateRandomCoordinate(GAME_UPPER_BORDER_Y, GAME_LOWER_BORDER_Y - zombieHeight);

		game->zombies[i]->body = newCollisionArea(game->zombies[i]->x, game->zombies[i]->y, game->zombies[i]->x + zombieWidth, game->zombies[i]->y + zombieHeight);
	}
}

void initShots() {
	MinixForce* game = getGame();

	int shotWidth = game->shots[0]->bullet.width;
	int shotHeight = game->shots[0]->bullet.height;

	for (int i = 0; i < MAX_NUMBER_OF_SHOTS; i++) {
		game->shots[i]->body = newCollisionArea(game->shots[i]->x, game->shots[i]->y, game->shots[i]->x + shotWidth, game->shots[i]->y + shotHeight);
	}
}
