#include "movement.h"

void updateMinixForce()
{

	MinixForce *game = getGame();

	//check if the soldade is alive
	if (game->lifes <= 0)
		updateGameState(SCORE);

	game->time_ticket = 0;

	game->MFstateGame = getStateGame();
	game->MFstateMain = getStateMain();
	game->MFstateMouse = getStateMouse();
	game->MFstatePlayer = getStatePlayer();
	game->MFstateScore = getStateScore();

	if (game->MFstateGame == MAIN_MENU){
		rtc_ih();
	}
		
	else if (game->MFstateGame == GAME)
		events();

	else if (game->MFstateGame == END_MENU)
		game->endEnd = true;

	else if (game->MFstateGame == COUNT_DOWN ){
		updateCount();
	}

}

void events()
{
	updateScore();
	updateSoldier();
	updateShots();
	checkCollisions();
}

void updateSoldier()
{
	MinixForce *game = getGame();
	switch (game->MFstatePlayer)
	{
	case FRONT:
		moveSoldierFront();
		break;
	case BACK:
		moveSoldierBack();
		break;
	case PUP:
		moveSoldierUp();
		break;
	case PDOWN:
		moveSoldierDown();
		break;
	case DEFAULT:
		break;
	}
}

void moveSoldierUp()
{
	MinixForce *game = getGame();

	int newY = game->soldier->y - PLAYER_SPEED;
	int soldierHeight = game->soldier->soldierFwd.height;

	updatePlayerState(DEFAULT);
	if (newY > GAME_UPPER_BORDER_Y)
	{
		game->soldier->y = newY;
		game->soldier->body->y1 = newY;
		game->soldier->body->y2 = newY + soldierHeight;
	}
}

void moveSoldierDown()
{
	MinixForce *game = getGame();

	int newY = game->soldier->y + PLAYER_SPEED;
	int soldierHeight = game->soldier->soldierFwd.height;

	updatePlayerState(DEFAULT);
	if (newY < GAME_LOWER_BORDER_Y - soldierHeight)
	{
		game->soldier->y = newY;
		game->soldier->body->y1 = newY;
		game->soldier->body->y2 = newY + soldierHeight;
	}
}

void moveSoldierBack()
{
	MinixForce *game = getGame();

	int newX = game->soldier->x - PLAYER_SPEED;
	int soldierWidth = game->soldier->soldierFwd.width;

	updatePlayerState(DEFAULT);
	if (newX > GAME_UPPER_BORDER_X)
	{
		game->soldier->x = newX;
		game->soldier->body->x1 = newX;
		game->soldier->body->x2 = newX + soldierWidth;
	}
}

void moveSoldierFront()
{
	MinixForce *game = getGame();

	int newX = game->soldier->x + PLAYER_SPEED;
	int soldierWidth = game->soldier->soldierFwd.width;

	updatePlayerState(DEFAULT);
	if (newX < GAME_LOWER_BORDER_X - soldierWidth)
	{
		game->soldier->x = newX;
		game->soldier->body->x1 = newX;
		game->soldier->body->x2 = newX + soldierWidth;
	}
}

void resetSoldierPosition()
{
	MinixForce *game = getGame();

	int soldierWidth = game->soldier->soldierFwd.width;
	int soldierHeight = game->soldier->soldierFwd.height;

	game->soldier->x = PLAYER_INITIAL_POSITION_X;
	game->soldier->y = PLAYER_INITIAL_POSITION_Y;

	game->soldier->body->x1 = game->soldier->x;
	game->soldier->body->y1 = game->soldier->y;
	game->soldier->body->x2 = game->soldier->x + soldierWidth;
	game->soldier->body->y2 = game->soldier->y + soldierHeight;
}

void resetCrosshairPosition()
{
	MinixForce *game = getGame();

	game->crosshair->x = CROSSHAIR_INITIAL_POSITION_X;
	game->crosshair->y = CROSSHAIR_INITIAL_POSITION_Y;
}

void updateScore()
{
	MinixForce *game = getGame();
	game->score = game->time_alive / 60 + game->enemiesKilled * 15;
}

void updateZombiesPositions()
{
	MinixForce *game = getGame();

	int speed = ZOMBIE_SPEED + (ZOMBIE_SPEED * floor(game->time_alive / (60 * 30)));
	
	int newX;

	int width = game->zombies[0]->zombie_sprites[ZOMBIE_MIDDLE_SPRITE].width;

	for (int i = 0; i < NUMBER_OF_ZOMBIES; i++)
	{
		newX = game->zombies[i]->x - speed;

		game->zombies[i]->x = newX;
		game->zombies[i]->body->x1 = newX;
		game->zombies[i]->body->x2 = newX + width;

		/* If zombie is out of the screen recalculate position decrement 5 points */
		if (newX < GAME_UPPER_BORDER_X) {
			recalculateZombiePosition(game->zombies[i]);
		}
	}
}

void resetZombiesPositions()
{
	MinixForce *game = getGame();

	for (int i = 0; i < NUMBER_OF_ZOMBIES; i++)
	{
		recalculateZombiePosition(game->zombies[i]);
	}
}

void recalculateZombiePosition(Enemy *zombie)
{

	int height = zombie->zombie_sprites[ZOMBIE_MIDDLE_SPRITE].height;
	int width = zombie->zombie_sprites[ZOMBIE_MIDDLE_SPRITE].width;

	/* Adding GAME_LOWER_BORDER_X ensures that the zombies take a while before appearing back on screen */
	int newX = GAME_LOWER_BORDER_X + generateRandomCoordinate(GAME_UPPER_BORDER_X, GAME_LOWER_BORDER_X);
	int newY = generateRandomCoordinate(GAME_UPPER_BORDER_Y, GAME_LOWER_BORDER_Y - height);

	zombie->x = newX;
	zombie->y = newY;

	zombie->body->x1 = newX;
	zombie->body->y1 = newY;
	zombie->body->x2 = newX + width;
	zombie->body->y2 = newY + height;
}

void updateShots()
{
	MinixForce *game = getGame();

	/* Checking if a new shot is being fired */
	if (game->MFstateMouse == FIRE)
	{
		for (int i = 0; i < MAX_NUMBER_OF_SHOTS; i++)
		{
			if (!(game->shots[i]->useBullet))
			{
				game->shots[i]->useBullet = true;
				calculateShotSpeed(game->shots[i]);
				break;
			}
		}
		updateMouseState(DEF);
	}

	/* Updating the shots location if they have been fired */
	for (int i = 0; i < MAX_NUMBER_OF_SHOTS; i++)
	{
		if (game->shots[i]->useBullet)
		{
			updateShot(game->shots[i]);
		}
	}
}

void updateShot(Shot *bullet)
{

	int bulletWidth = bullet->bullet.width;
	int bulletHeight = bullet->bullet.height;

	bullet->x += bullet->xSpeed;
	bullet->y += bullet->ySpeed;

	bullet->body->x1 = bullet->x;
	bullet->body->y1 = bullet->y;
	bullet->body->x2 = bullet->x + bulletWidth;
	bullet->body->y2 = bullet->y + bulletHeight;

	/* If shot is out of the screen dont use it */
	if (bullet->x > GAME_LOWER_BORDER_X || bullet->y > GAME_LOWER_BORDER_Y || bullet->y < GAME_UPPER_BORDER_Y)
		bullet->useBullet = false;
}

void calculateShotSpeed(Shot *bullet)
{
	MinixForce *game = getGame();
	int bulletWidth = bullet->bullet.width;
	int bulletHeight = bullet->bullet.height;
	uint16_t soldierWidth = game->soldier->soldierFwd.width;
	uint16_t soldierHeight = game->soldier->soldierFwd.height;
	uint16_t soldierXPosition = game->soldier->x;
	uint16_t soldierYPosition = game->soldier->y;
	uint16_t soldierMiddleXPosition = soldierXPosition + soldierWidth / 2;
	uint16_t soldierMiddleYPosition = soldierYPosition + soldierHeight / 2 + 18;
	bullet->x = game->soldier->x + soldierWidth - bulletWidth / 2;
	bullet->y = soldierMiddleYPosition - bulletHeight / 2;
	uint16_t crosshairWidth = game->crosshair->aim.width;
	uint16_t crosshairHeight = game->crosshair->aim.height;
	uint16_t crosshairXPosition = game->crosshair->x;
	uint16_t crosshairYPosition = game->crosshair->y;
	uint16_t crosshairMiddleXPosition = crosshairXPosition + crosshairWidth / 2;
	uint16_t crosshairMiddleYPosition = crosshairYPosition + crosshairHeight / 2;

	/* Calculating Speed */
	float triangleWidth = crosshairMiddleXPosition - soldierMiddleXPosition;
	float triangleHeight = -(soldierMiddleYPosition - crosshairMiddleYPosition);
	float triangleHypotenuse = sqrt(triangleWidth * triangleWidth + triangleHeight * triangleHeight);
	bullet->xSpeed = SHOT_SPEED * (triangleWidth / triangleHypotenuse);
	bullet->ySpeed = SHOT_SPEED * (triangleHeight / triangleHypotenuse);
}

void checkCollisions()
{
	checkShotCollisions();
	checkPlayerCollisions();
}

void checkShotCollisions()
{
	MinixForce *game = getGame();

	for (int i = 0; i < NUMBER_OF_ZOMBIES; i++)
	{
		for (int j = 0; j < MAX_NUMBER_OF_SHOTS; j++)
		{
			if (game->shots[j]->useBullet)
			{
				if (collision(game->zombies[i]->body, game->shots[j]->body))
				{
					game->enemiesKilled++;
					recalculateZombiePosition(game->zombies[i]);
					game->shots[j]->useBullet = false;
				}
			}
		}
	}
}

void checkPlayerCollisions()
{
	MinixForce *game = getGame();

	for (int i = 0; i < NUMBER_OF_ZOMBIES; i++)
	{
		if (collision(game->zombies[i]->body, game->soldier->body))
		{
			game->lifes--;
			recalculateZombiePosition(game->zombies[i]);
		}
	}
}

void updateCount()
{
	MinixForce *game = getGame();
	if(game->countDown >= 1 ){
		game->countDown -= 0.2;
	}
	else
	{
		updateGameState(SPLAYER);
		game->MFstateGame = GAME;
		game->countDown = 4*60;
	}
}
