#include "minixforce.h"

static MinixForce *game = NULL;

MinixForce * initMinixForce() {
  /* GAME INITIALIZATION */
  game = (MinixForce *) malloc(sizeof(MinixForce));
  game->real_time =(rtc_time_t*) malloc(sizeof(rtc_time_t));
   
  if(subscribes())
    return NULL;
 
  initValues();

	createEntities();
  
	loadXPMs();

	initMainMenu();

  initScoreMenu();

  initSoldier();

  initCrosshair();

  initEnemies();

	initShots();

  return game;
}

void initValues(){
  game->time_ticket = 0;
  game->time_alive = 0;
  game->lifes = MAX_LIFES;
  game->score = 0;
  game->enemiesKilled = 0;
  game->countDown = 4*60;
  game->endEnd = false;
  updateGameState(MAIN);
  updateMouseState(DEF);
}

MinixForce *getGame() {
  if (game == NULL) {
    game = initMinixForce();
  }
  return game;
}


void restartMinixForce(){
  
  initValues();

  // restart entities positions
  resetSoldierPosition();

  resetCrosshairPosition();

  resetZombiesPositions();

  updateMouseState(DEF);
}

void endMinixForce() {

  game->endEnd = true;

  unsubscribes();

  deleteAllCollisionAreas();
  deleteXPMs();
  free(game->real_time);
  free(game->main_menu);
  free(game->score_menu);
  free(game->soldier);
  for (int i = 0; i < NUMBER_OF_ZOMBIES; i++) {
    free(game->zombies[i]);
  }
  for (int i = 0; i < MAX_NUMBER_OF_SHOTS; i++) {
    free(game->shots[i]);
  }
  free(game->crosshair);
	free(game);

}
