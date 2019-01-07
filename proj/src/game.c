#include <lcom/lcf.h>
#include "game.h"
#include "interrupts.h"
#include "utils.h"
#include "graphics.h"
#include "movement.h"

int play(){

	//if it can not subscribe some controller.
	if(stGame()){
		endGame(); //leave vg mode and free memory
		return 1;
	}		
	gamePlay();
	endGame();
	return 0;
}

int stGame() {
	
	//inits the game mode
	if(vg_init(MINIXFORCE_GAME_MODE) == NULL)
		return 1;

	//initializes all variables
	if(initMinixForce() == NULL) 
		return 1;

	return 0;
}

void gamePlay() {
	MinixForce * game = getGame();
	drawMinixForce();
	while (!game->endEnd) {
		//leaves interrupt handler when there is a interrupt
		interruptHandler();
		//updates the new state of everything
		updateMinixForce();
		//draws the differences
		drawMinixForce();		
	}
	return;
}

int endGame(){
	MinixForce * game = getGame();
	endMinixForce(game);
	if(vg_exit())
		return 1;
	return 0;
}
