#include "xpm.h"

void loadXPMs() {
	loadMainMenuXPMs();
	loadScoreMenuXPMs();
  loadSoldierXPM();
	loadZombieXPM();
	loadGameBackgroundXPMs();
	loadCrosshairXPM();
	loadShotXPMs();
	loadDigitXPMs();
}

void loadMainMenuXPMs() {
	MinixForce* game = getGame();

	/* Loading main menu & help menu background */
	xpm_image_t* background = &game->main_menu->menuBackground;
	xpm_load(main_menu_background_xpm, XPM_8_8_8_8, background);
	xpm_image_t* helpBackground = &game->main_menu->helpBackground;
	xpm_load(help_menu_background_xpm, XPM_8_8_8_8, helpBackground);

	/* Loading normal buttons */
  xpm_image_t* playButtonNormal = &game->main_menu->playButton->normal;
  xpm_image_t* helpButtonNormal = &game->main_menu->helpButton->normal;
  xpm_image_t* quitButtonNormal = &game->main_menu->quitButton->normal;
  xpm_load(play_button_xpm, XPM_8_8_8_8, playButtonNormal);
  xpm_load(help_button_xpm, XPM_8_8_8_8, helpButtonNormal);
  xpm_load(quit_button_xpm, XPM_8_8_8_8, quitButtonNormal);
	/* Loading selected buttons */
  xpm_image_t* playButtonSelected = &game->main_menu->playButton->selected;
  xpm_image_t* helpButtonSelected = &game->main_menu->helpButton->selected;
  xpm_image_t* quitButtonSelected = &game->main_menu->quitButton->selected;
  xpm_load(play_button_selected_xpm, XPM_8_8_8_8, playButtonSelected);
  xpm_load(help_button_selected_xpm, XPM_8_8_8_8, helpButtonSelected);
  xpm_load(quit_button_selected_xpm, XPM_8_8_8_8, quitButtonSelected);
}

void loadScoreMenuXPMs() {
	MinixForce* game = getGame();

	/* Loading main menu & help menu background */
	xpm_image_t* background = &game->score_menu->menuBackground;
	xpm_load(score_menu_background_xpm, XPM_8_8_8_8, background);

	/* Loading normal buttons */
  xpm_image_t* backMainButtonNormal = &game->score_menu->backMainButton->normal;
  xpm_image_t* restartButtonNormal = &game->score_menu->restartButton->normal;
  xpm_image_t* quitButtonNormal = &game->score_menu->quitButton->normal;
  xpm_load(main_menu_button_xpm, XPM_8_8_8_8, backMainButtonNormal);
  xpm_load(play_button_xpm, XPM_8_8_8_8, restartButtonNormal);
  xpm_load(quit_button_xpm, XPM_8_8_8_8, quitButtonNormal);
	/* Loading selected buttons */
  xpm_image_t* backMainButtonSelected = &game->score_menu->backMainButton->selected;
  xpm_image_t* restartButtonSelected = &game->score_menu->restartButton->selected;
  xpm_image_t* quitButtonSelected = &game->score_menu->quitButton->selected;
  xpm_load(main_menu_button_selected_xpm, XPM_8_8_8_8, backMainButtonSelected);
  xpm_load(play_button_selected_xpm, XPM_8_8_8_8, restartButtonSelected);
  xpm_load(quit_button_selected_xpm, XPM_8_8_8_8, quitButtonSelected);
}

void loadSoldierXPM() {
  MinixForce* game = getGame();
  xpm_image_t* soldierForward = &game->soldier->soldierFwd;
  xpm_load(soldier_xpm, XPM_8_8_8_8, soldierForward);
}

void loadZombieXPM() {
	MinixForce* game = getGame();
	for (int i = 0; i < NUMBER_OF_ZOMBIES; i++) {
		xpm_image_t* zombie_right = &game->zombies[i]->zombie_sprites[ZOMBIE_RIGHT_SPRITE];
		xpm_load(zombie_right_xpm, XPM_8_8_8_8, zombie_right);
		xpm_image_t* zombie_right_middle = &game->zombies[i]->zombie_sprites[ZOMBIE_RIGHT_MIDDLE_SPRITE];
		xpm_load(zombie_right_middle_xpm, XPM_8_8_8_8, zombie_right_middle);
		xpm_image_t* zombie_middle = &game->zombies[i]->zombie_sprites[ZOMBIE_MIDDLE_SPRITE];
		xpm_load(zombie_middle_xpm, XPM_8_8_8_8, zombie_middle);
		xpm_image_t* zombie_left_middle = &game->zombies[i]->zombie_sprites[ZOMBIE_LEFT_MIDDLE_SPRITE];
		xpm_load(zombie_left_middle_xpm, XPM_8_8_8_8, zombie_left_middle);
		xpm_image_t* zombie_left = &game->zombies[i]->zombie_sprites[ZOMBIE_LEFT_SPRITE];
		xpm_load(zombie_left_xpm, XPM_8_8_8_8, zombie_left);
		/*
		xpm_image_t* zombie_right = &game->zombies[i]->zombie_right;
		xpm_load(zombie_right_xpm, XPM_8_8_8_8, zombie_right);
		xpm_image_t* zombie_right_middle = &game->zombies[i]->zombie_right_middle;
		xpm_load(zombie_right_middle_xpm, XPM_8_8_8_8, zombie_right_middle);
		xpm_image_t* zombie_middle = &game->zombies[i]->zombie_middle;
		xpm_load(zombie_middle_xpm, XPM_8_8_8_8, zombie_middle);
		xpm_image_t* zombie_left_middle = &game->zombies[i]->zombie_left_middle;
		xpm_load(zombie_left_middle_xpm, XPM_8_8_8_8, zombie_left_middle);
		xpm_image_t* zombie_left = &game->zombies[i]->zombie_left;
		xpm_load(zombie_left_xpm, XPM_8_8_8_8, zombie_left);
		*/
	}
}

void loadCrosshairXPM() {
  MinixForce* game = getGame();

  xpm_image_t* aim = &game->crosshair->aim;
  xpm_load(crosshair_xpm, XPM_8_8_8_8, aim);
}

void loadShotXPMs() {
  MinixForce* game = getGame();
	for (int i = 0; i < MAX_NUMBER_OF_SHOTS; i++) {
		xpm_image_t* shot = &game->shots[i]->bullet;
		xpm_load(arcade_shot_xpm, XPM_8_8_8_8, shot);
	}
}

void loadGameBackgroundXPMs() {
	MinixForce* game = getGame();
  xpm_image_t* tile = &game->tileBackground;
  xpm_image_t* upper = &game->upperBackground;
  xpm_load(game_background_tile_xpm, XPM_8_8_8_8, tile);
  xpm_load(game_background_upper_xpm, XPM_8_8_8_8, upper);

	/* Loading Heart XPM */
	xpm_image_t* heart = &game->heart;
	xpm_load(arcade_heart_xpm, XPM_8_8_8_8, heart);

	/* Loading Paused XPM */
	xpm_image_t* paused = &game->paused;
	xpm_load(arcade_pause_xpm, XPM_8_8_8_8, paused);
}

void loadDigitXPMs() {
	MinixForce* game = getGame();
  xpm_load(arcade_0_xpm, XPM_8_8_8_8, &game->digits[0]);
  xpm_load(arcade_1_xpm, XPM_8_8_8_8, &game->digits[1]);
	xpm_load(arcade_2_xpm, XPM_8_8_8_8, &game->digits[2]);
	xpm_load(arcade_3_xpm, XPM_8_8_8_8, &game->digits[3]);
	xpm_load(arcade_4_xpm, XPM_8_8_8_8, &game->digits[4]);
	xpm_load(arcade_5_xpm, XPM_8_8_8_8, &game->digits[5]);
	xpm_load(arcade_6_xpm, XPM_8_8_8_8, &game->digits[6]);
	xpm_load(arcade_7_xpm, XPM_8_8_8_8, &game->digits[7]);
	xpm_load(arcade_8_xpm, XPM_8_8_8_8, &game->digits[8]);
	xpm_load(arcade_9_xpm, XPM_8_8_8_8, &game->digits[9]);
	xpm_load(arcade_dots_xpm, XPM_8_8_8_8, &game->digits[10]);
	xpm_load(arcade_slash_xpm, XPM_8_8_8_8, &game->digits[11]);
}

void drawXPM(xpm_image_t* xpm, int x, int y) {

	if (xpm == NULL)
		return;

	int horizontalRes = get_hres();
	int verticalRes = get_vres();

	int width = xpm->width;
	int drawWidth = width;
	int height = xpm->height;

  
	if (x + width < 0 || x > horizontalRes || y + height < 0 || y > verticalRes)
		return;

	int xCorrection = 0;
	if (x < 0) {
		xCorrection = -x;
		drawWidth -= xCorrection;
		x = 0;

		if (drawWidth > horizontalRes)
			drawWidth = horizontalRes;
	}
	else if (x + drawWidth >= horizontalRes) {
		drawWidth = horizontalRes - x;
	}

	char* bufferStartPos;
	char* imgStartPos;
  int bytesPerPixel = get_bytes_per_pixel();

	for (int i = 0; i < height; i++) {
		int line = y + i;

		if (line < 0 || line >= verticalRes)
			continue;

		bufferStartPos = get_tmp_video_mem();
		bufferStartPos += x * bytesPerPixel + line * horizontalRes * bytesPerPixel;

		imgStartPos = (char*)(xpm->bytes + xCorrection * bytesPerPixel + i * width * bytesPerPixel);

		//paint everything expect TRANSPARENCY_COLOR (set as background of sprites);
		for (int j = 0; j < drawWidth * bytesPerPixel; j += bytesPerPixel) {

      uint32_t color = imgStartPos[j];
      color |= imgStartPos[j+1] << 8;
      color |= imgStartPos[j+2] << 16;
      color |= imgStartPos[j+3] << 24;

			if (color != TRANSPARENCY_COLOR_8_8_8_8) {
				bufferStartPos[j] = imgStartPos[j];
				bufferStartPos[j + 1] = imgStartPos[j + 1];
        bufferStartPos[j + 2] = imgStartPos[j + 2];
			}

		}
	}
}

void deleteXPMs() {
	MinixForce* game = getGame();

	/* Delete Main Menu Content */
	deleteXPM(&game->main_menu->menuBackground);
	deleteXPM(&game->main_menu->helpBackground);
	deleteXPM(&game->main_menu->playButton->normal);
	deleteXPM(&game->main_menu->playButton->selected);
	deleteXPM(&game->main_menu->helpButton->normal);
	deleteXPM(&game->main_menu->helpButton->selected);
	deleteXPM(&game->main_menu->quitButton->normal);
	deleteXPM(&game->main_menu->quitButton->selected);

	/* Delete Score Menu Content */
	deleteXPM(&game->score_menu->menuBackground);
	deleteXPM(&game->score_menu->backMainButton->normal);
	deleteXPM(&game->score_menu->backMainButton->selected);
	deleteXPM(&game->score_menu->quitButton->normal);
	deleteXPM(&game->score_menu->quitButton->selected);
	deleteXPM(&game->score_menu->restartButton->normal);
	deleteXPM(&game->score_menu->restartButton->selected);

	/* Delete Soldier XPM */
	deleteXPM(&game->soldier->soldierFwd);

	/* Delete Zombie XPM */
	for (int i = 0; i < NUMBER_OF_ZOMBIES; i++) {
		for (int j = 0; j < NUMBER_OF_ZOMBIE_SPRITES; j++) {
			deleteXPM(&game->zombies[i]->zombie_sprites[j]);
		}
	}

	/* Delete crosshair XPM */
	deleteXPM(&game->crosshair->aim);

	/* Delete Shot XPM */
	for (int i = 0; i < MAX_NUMBER_OF_SHOTS; i++) {
		deleteXPM(&game->shots[i]->bullet);
	}

	/* Delete Digits XPMs */
	for (int i = 0; i < NUMBER_OF_DIGITS; i++) {
		deleteXPM(&game->digits[i]);
	}

	/* Delete miscellaneous XPMs */
	deleteXPM(&game->paused);
	deleteXPM(&game->heart);
	deleteXPM(&game->tileBackground);
	deleteXPM(&game->upperBackground);
}

void deleteXPM(xpm_image_t* xpm) {
	if (xpm == NULL)
		return;

	free(xpm->bytes);
	free(xpm);
}
