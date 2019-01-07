#include "states.h"

static stateGAME stateGame = MAIN_MENU;

static statePLAYER statePlayer = DEFAULT;

static stateMOUSE stateMouse = DEF;

static stateMAIN stateMain = MPLAY;

static stateSCORE stateScore = B_TO_MAIN;

void updateMouseState(stateMOUSE newState) {
	stateMouse = newState;
}

void updatePlayerState(statePLAYER newState) {
	statePlayer = newState;
}

void updateScoreState(menu_event_t Eevent)
{
	switch(stateScore){

		case B_TO_MAIN: 
			if(Eevent == ENTER){
				updateGameState(MAIN);
			}
			else if(Eevent == KDOWN){
				stateScore = RESTART;
			}
			break;

		case RESTART:
			if(Eevent == ENTER){
				updateGameState(COUNT);
			}
			else if(Eevent == KUP){
				stateScore = B_TO_MAIN;	
			}
			else if(Eevent == KDOWN){
				stateScore = LEAVE;
			}
				

			break;

		case LEAVE:
			if(Eevent == ENTER){
				updateGameState(EXIT);
			}
			else if(Eevent == KUP)
				stateScore = RESTART;

		break;

	}
}

void updateMainState(menu_event_t Mevent){
	
	switch (stateMain) {

	case MPLAY:
		if(Mevent == ENTER){
			updateGameState(COUNT);
		}
			
		else if(Mevent == KDOWN)
			stateMain = MHELP;

		break;

	case MHELP:
		if(Mevent == ENTER)
			updateGameState(HELP);

		else if(Mevent == KUP)
			stateMain = MPLAY;	

		else if(Mevent == KDOWN)
			stateMain = MEXIT;

		break;

	case MEXIT:
		if(Mevent == ENTER)
			updateGameState(EXIT);

		else if(Mevent == KUP)
			stateMain = MHELP;

		break;	
	}

}

void updateGameState(game_event_t Gevent) {

	switch (stateGame) {

	case MAIN_MENU:
		if(Gevent == COUNT)
			stateGame = COUNT_DOWN;

		if(Gevent == HELP)
			stateGame = HELP_MENU;

		if (Gevent == EXIT)
			stateGame = END_MENU;
		break;

	case HELP_MENU:
		if(Gevent == MAIN)
			stateGame = MAIN_MENU;
		break;

	case GAME:
		if (Gevent == SCORE){	
			stateGame = SCORE_MENU;
		}
		if (Gevent == PAUSE){	
			stateGame = PAUSE_MENU;
		}
		break;

	case COUNT_DOWN:
		if(Gevent == SPLAYER)
			stateGame = GAME;
		break;

	case PAUSE_MENU:
		if(Gevent == COUNT)
			stateGame = COUNT_DOWN;
		break;

	case SCORE_MENU:
		if(Gevent == MAIN){
			stateGame = MAIN_MENU;
		}

		if(Gevent == COUNT)
			stateGame = COUNT_DOWN;

		if (Gevent == EXIT)
			stateGame = END_MENU;
		break;

	case END_MENU:
		break;
	}

}

stateMAIN getStateMain(){
    return stateMain;
}

stateGAME getStateGame(){
    return stateGame;
}

statePLAYER getStatePlayer(){
    return statePlayer;
}

stateMOUSE getStateMouse(){
    return stateMouse;
}

stateSCORE getStateScore(){
	return stateScore;
}

