#include "lcom/lcf.h"
#include "graphics.h"
#include "utils.h"
#include <math.h>

void drawMinixForce()
{

  MinixForce *game = getGame();

  switch (game->MFstateGame)
  {

  case MAIN_MENU:
    drawMainMenu();
    break;

  case HELP_MENU:
    drawHelpMenu();
    break;

  case GAME:
    drawGame();
    break;

  case COUNT_DOWN:
    drawGame();
    break;

  case PAUSE_MENU:
    drawPauseMenu();
    break;

  case SCORE_MENU:
    drawScoreMenu();
    break;

  case END_MENU:
    /* Game closed, do nothing */
    break;
  }

  /* Draws on VRAM memory */
  flip_double_buffer();

  return;
}

void drawMainMenu() {

  MinixForce *game = getGame();

  /* Crosshair - TESTING PURPOSES */
  drawXPM(&game->crosshair->aim, game->crosshair->x, game->crosshair->y);

  /* Drawing background */
  drawXPM(&game->main_menu->menuBackground, BACKGROUND_ORIGIN_COORDS, BACKGROUND_ORIGIN_COORDS);

  /* Play Button */
  if (game->MFstateMain == MPLAY) {
    drawXPM(&game->main_menu->playButton->selected, game->main_menu->playButton->x, game->main_menu->playButton->y);
  }
  else {
    drawXPM(&game->main_menu->playButton->normal, game->main_menu->playButton->x, game->main_menu->playButton->y);
  }
  /* Help Button */
  if (game->MFstateMain == MHELP) {
    drawXPM(&game->main_menu->helpButton->selected, game->main_menu->helpButton->x, game->main_menu->helpButton->y);
  }
  else {
    drawXPM(&game->main_menu->helpButton->normal, game->main_menu->helpButton->x, game->main_menu->helpButton->y);
  }
  /* Quit Button */
  if (game->MFstateMain == MEXIT) {
    drawXPM(&game->main_menu->quitButton->selected, game->main_menu->quitButton->x, game->main_menu->quitButton->y);
  }
  else {
    drawXPM(&game->main_menu->quitButton->normal, game->main_menu->quitButton->x, game->main_menu->quitButton->y);
  }

  /*   draw day   */
  unsigned int dones = game->real_time->day % 10;
  unsigned int dtens = (int)floor(game->real_time->day / 10) % 10;
  drawXPM(&game->digits[dtens], RTC_DAY_TENS_POSITION_X, RTC_DATE_POSITION_Y);
  drawXPM(&game->digits[dones], RTC_DAY_ONES_POSITION_X, RTC_DATE_POSITION_Y);
  /* Drawing dots */
  drawXPM(&game->digits[DIGIT_SLASH_INDEX], RTC_SLASH_1_POSITION_X, RTC_DATE_POSITION_Y);
  /* draw mouth */
  unsigned int mones = game->real_time->month % 10;
  unsigned int mtens = (int)floor(game->real_time->month / 10) % 10;
  /* Drawing tens */
  drawXPM(&game->digits[mtens], RTC_MONTH_TENS_POSITION_X, RTC_DATE_POSITION_Y);
  /* Drawing ones */
  drawXPM(&game->digits[mones], RTC_MONTH_ONES_POSITION_X, RTC_DATE_POSITION_Y);

  /* Drawing dots */
  drawXPM(&game->digits[DIGIT_SLASH_INDEX], RTC_SLASH_2_POSITION_X, RTC_DATE_POSITION_Y);
  //draw year
  unsigned int yones = game->real_time->year % 10;
  unsigned int ytens = (int)floor(game->real_time->year / 10) % 10;
  unsigned int yhundreds = (int)floor(game->real_time->year / 100) % 10;
  unsigned int ythousands = (int)floor(game->real_time->year / 1000) % 10;
  /* Drawing thousands */
  drawXPM(&game->digits[ythousands], RTC_YEAR_THOUSANDS_POSITION_X, RTC_DATE_POSITION_Y);
  /* Drawing hundreds */
  drawXPM(&game->digits[yhundreds], RTC_YEAR_HUNDREDS_POSITION_X, RTC_DATE_POSITION_Y);
  /* Drawing tens */
  drawXPM(&game->digits[ytens], RTC_YEAR_TENS_POSITION_X, RTC_DATE_POSITION_Y);
  /* Drawing ones */
  drawXPM(&game->digits[yones], RTC_YEAR_ONES_POSITION_X, RTC_DATE_POSITION_Y);

  unsigned int seconds_digit_1 = game->real_time->sec % 10;
  unsigned int seconds_digit_2 = (int)floor(game->real_time->sec / 10) % 10;
  unsigned int minutes_digit_1 = game->real_time->min % 10;
  unsigned int minutes_digit_2 = (int)floor(game->real_time->min / 10) % 10;
  unsigned int hour_digit_1 = game->real_time->hour % 10;
  unsigned int hour_digit_2 = (int)floor(game->real_time->hour / 10) % 10;

  /* Drawing minutes */
  drawXPM(&game->digits[hour_digit_2], RTC_CLOCK_HOURS_DIG2_POSITION_X, RTC_CLOCK_POSITION_Y);
  drawXPM(&game->digits[hour_digit_1], RTC_CLOCK_HOURS_DIG1_POSITION_X, RTC_CLOCK_POSITION_Y);
  /* Drawing dots */
  drawXPM(&game->digits[DIGIT_DOTS_INDEX], RTC_DOTS_1_POSITION_X, RTC_CLOCK_POSITION_Y);
  /* Drawing minutes */
  drawXPM(&game->digits[minutes_digit_2], RTC_CLOCK_MINS_DIG2_POSITION_X, RTC_CLOCK_POSITION_Y);
  drawXPM(&game->digits[minutes_digit_1], RTC_CLOCK_MINS_DIG1_POSITION_X, RTC_CLOCK_POSITION_Y);
  /* Drawing dots */
  drawXPM(&game->digits[DIGIT_DOTS_INDEX], RTC_DOTS_2_POSITION_X, RTC_CLOCK_POSITION_Y);
  /* Drawing seconds */
  drawXPM(&game->digits[seconds_digit_2], RTC_CLOCK_SECS_DIG2_POSITION_X, RTC_CLOCK_POSITION_Y);
  drawXPM(&game->digits[seconds_digit_1], RTC_CLOCK_SECS_DIG1_POSITION_X, RTC_CLOCK_POSITION_Y);
}

void drawHelpMenu() {
  MinixForce *game = getGame();

  /* Drawing background */
  drawXPM(&game->main_menu->helpBackground, BACKGROUND_ORIGIN_COORDS, BACKGROUND_ORIGIN_COORDS);

  if (game->time_alive % 60 <= 6)
    drawXPM(&game->zombies[0]->zombie_sprites[ZOMBIE_RIGHT_SPRITE], HELP_MENU_ZOMBIE_POSITION_X, HELP_MENU_ZOMBIE_POSITION_Y);
  else if (game->time_alive % 60 <= 13)
    drawXPM(&game->zombies[0]->zombie_sprites[ZOMBIE_RIGHT_MIDDLE_SPRITE], HELP_MENU_ZOMBIE_POSITION_X, HELP_MENU_ZOMBIE_POSITION_Y);
  else if (game->time_alive % 60 <= 20)
    drawXPM(&game->zombies[0]->zombie_sprites[ZOMBIE_MIDDLE_SPRITE], HELP_MENU_ZOMBIE_POSITION_X, HELP_MENU_ZOMBIE_POSITION_Y);
  else if (game->time_alive % 60 <= 26)
    drawXPM(&game->zombies[0]->zombie_sprites[ZOMBIE_LEFT_MIDDLE_SPRITE], HELP_MENU_ZOMBIE_POSITION_X, HELP_MENU_ZOMBIE_POSITION_Y);
  else if (game->time_alive % 60 <= 33)
    drawXPM(&game->zombies[0]->zombie_sprites[ZOMBIE_LEFT_SPRITE], HELP_MENU_ZOMBIE_POSITION_X, HELP_MENU_ZOMBIE_POSITION_Y);
  else if (game->time_alive % 60 <= 40)
    drawXPM(&game->zombies[0]->zombie_sprites[ZOMBIE_LEFT_MIDDLE_SPRITE], HELP_MENU_ZOMBIE_POSITION_X, HELP_MENU_ZOMBIE_POSITION_Y);
  else if (game->time_alive % 60 <= 46)
    drawXPM(&game->zombies[0]->zombie_sprites[ZOMBIE_MIDDLE_SPRITE], HELP_MENU_ZOMBIE_POSITION_X, HELP_MENU_ZOMBIE_POSITION_Y);
  else if (game->time_alive % 60 <= 53)
    drawXPM(&game->zombies[0]->zombie_sprites[ZOMBIE_RIGHT_MIDDLE_SPRITE], HELP_MENU_ZOMBIE_POSITION_X, HELP_MENU_ZOMBIE_POSITION_Y);
  else if (game->time_alive % 60 <= 60)
    drawXPM(&game->zombies[0]->zombie_sprites[ZOMBIE_RIGHT_SPRITE], HELP_MENU_ZOMBIE_POSITION_X, HELP_MENU_ZOMBIE_POSITION_Y);
}

void drawGame() {
  /* Drawing Background */
  drawGameBackground();

  /* Drawing Lifes */
  drawGameLifes();

  /* Drawing Soldier */
  drawSoldier();

  /* Drawing Shot */
  drawShot();

  /*Drawing enimies */
  drawEnemies();

  /* Drawing Score */
  drawGameScore();  

  /* Drawing Crosshair */
  drawCrosshair();

  MinixForce *game = getGame();

  if(game->MFstateGame == COUNT_DOWN)
  {
    game->time_alive = 0;
     drawXPM(&game->digits[(int)game->countDown/60], COUNT_INITIAL_POSITION_X,COUNT_INITIAL_POSITION_Y);
  }
 
  /* Drawing Time */
  drawGameTimer();

}

void drawPauseMenu()
{

  MinixForce *game = getGame();
  /* Drawing normal game background */
  drawGame();
  /* Drawing Paused XPM */
  drawXPM(&game->paused, PAUSED_POSITION_X, PAUSED_POSITION_Y);
}

void drawGameBackground() {
  // 1152x864 px
  MinixForce *game = getGame();
  int upperBackgroundWidth = game->upperBackground.width;
  // initial coordinates (0, 0)
  // Drawing upper background
  for (int i = 0; i < 8; i++)
  {
    drawXPM(&game->upperBackground, upperBackgroundWidth * i, BACKGROUND_ORIGIN_COORDS);
  }

  int tileBackgroundWidth = game->tileBackground.width;
  int tileBackgroundHeight = game->tileBackground.height;
  // initial coordinates (0, 100)
  // Drawing tile background
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      drawXPM(&game->tileBackground, tileBackgroundWidth * j, tileBackgroundHeight * i + GAME_UPPER_BORDER_Y);
    }
  }
}

void drawSoldier() {
  MinixForce *game = getGame();

  drawXPM(&game->soldier->soldierFwd, game->soldier->x, game->soldier->y);
}

void drawEnemies(){
  MinixForce *game = getGame();

  for (int i = 0; i < NUMBER_OF_ZOMBIES; i++) {
    if (game->time_alive % 60 <= 6)
      drawXPM(&game->zombies[i]->zombie_sprites[ZOMBIE_RIGHT_SPRITE], game->zombies[i]->x, game->zombies[i]->y);
    else if (game->time_alive % 60 <= 13)
      drawXPM(&game->zombies[i]->zombie_sprites[ZOMBIE_RIGHT_MIDDLE_SPRITE], game->zombies[i]->x, game->zombies[i]->y);
    else if (game->time_alive % 60 <= 20)
      drawXPM(&game->zombies[i]->zombie_sprites[ZOMBIE_MIDDLE_SPRITE], game->zombies[i]->x, game->zombies[i]->y);
    else if (game->time_alive % 60 <= 26)
      drawXPM(&game->zombies[i]->zombie_sprites[ZOMBIE_LEFT_MIDDLE_SPRITE], game->zombies[i]->x, game->zombies[i]->y);
    else if (game->time_alive % 60 <= 33)
      drawXPM(&game->zombies[i]->zombie_sprites[ZOMBIE_LEFT_SPRITE], game->zombies[i]->x, game->zombies[i]->y);
    else if (game->time_alive % 60 <= 40)
      drawXPM(&game->zombies[i]->zombie_sprites[ZOMBIE_LEFT_MIDDLE_SPRITE], game->zombies[i]->x, game->zombies[i]->y);
    else if (game->time_alive % 60 <= 46)
      drawXPM(&game->zombies[i]->zombie_sprites[ZOMBIE_MIDDLE_SPRITE], game->zombies[i]->x, game->zombies[i]->y);
    else if (game->time_alive % 60 <= 53)
      drawXPM(&game->zombies[i]->zombie_sprites[ZOMBIE_RIGHT_MIDDLE_SPRITE], game->zombies[i]->x, game->zombies[i]->y);
    else if (game->time_alive % 60 <= 60)
      drawXPM(&game->zombies[i]->zombie_sprites[ZOMBIE_RIGHT_SPRITE], game->zombies[i]->x, game->zombies[i]->y);
  }
}

void drawCrosshair() {
  MinixForce *game = getGame();

  drawXPM(&game->crosshair->aim, game->crosshair->x, game->crosshair->y);
}

void drawShot() {
  MinixForce *game = getGame();

  for (int i = 0; i < MAX_NUMBER_OF_SHOTS; i++) {
    if (game->shots[i]->useBullet)
      drawXPM(&game->shots[i]->bullet, game->shots[i]->x, game->shots[i]->y);
  }
}

void drawGameTimer()
{
  MinixForce *game = getGame();

  unsigned int timer = game->time_alive;
  unsigned int total_seconds = floor(timer / FREQ);
  unsigned int total_minutes = floor(total_seconds / 60);
  unsigned int seconds_mark = total_seconds % 60;
  unsigned int minutes_mark = total_minutes % 60;

  unsigned int seconds_digit_1 = seconds_mark % 10;
  unsigned int seconds_digit_2 = floor(seconds_mark / 10);

  unsigned int minutes_digit_1 = minutes_mark % 10;
  unsigned int minutes_digit_2 = floor(minutes_mark / 10);

  if (game->MFstateGame == SCORE_MENU) {
    /* Drawing minutes */
    drawXPM(&game->digits[minutes_digit_2], SCORE_MINUTES_DIG2_POSITION_X, SCORE_MINUTES_DIG2_POSITION_Y);
    drawXPM(&game->digits[minutes_digit_1], SCORE_MINUTES_DIG1_POSITION_X, SCORE_MINUTES_DIG1_POSITION_Y);
    /* Drawing dots */
    drawXPM(&game->digits[DIGIT_DOTS_INDEX], SCORE_DOTS_POSITION_X, SCORE_DOTS_POSITION_Y);
    /* Drawing seconds */
    drawXPM(&game->digits[seconds_digit_2], SCORE_SECONDS_DIG2_POSITION_X, SCORE_SECONDS_DIG2_POSITION_Y);
    drawXPM(&game->digits[seconds_digit_1], SCORE_SECONDS_DIG1_POSITION_X, SCORE_SECONDS_DIG1_POSITION_Y);
  }
  else  {
    /* Drawing minutes */
    drawXPM(&game->digits[minutes_digit_2], GAME_MINUTES_DIG2_POSITION_X, GAME_MINUTES_DIG2_POSITION_Y);
    drawXPM(&game->digits[minutes_digit_1], GAME_MINUTES_DIG1_POSITION_X, GAME_MINUTES_DIG1_POSITION_Y);
    /* Drawing dots */
    drawXPM(&game->digits[DIGIT_DOTS_INDEX], GAME_DOTS_POSITION_X, GAME_DOTS_POSITION_Y);
    /* Drawing seconds */
    drawXPM(&game->digits[seconds_digit_2], GAME_SECONDS_DIG2_POSITION_X, GAME_SECONDS_DIG2_POSITION_Y);
    drawXPM(&game->digits[seconds_digit_1], GAME_SECONDS_DIG1_POSITION_X, GAME_SECONDS_DIG1_POSITION_Y);
  }
  
}

void drawGameLifes()
{
  MinixForce *game = getGame();

  int lifes = game->lifes;

  for (int i = 0; i < lifes; i++)
  {
    drawXPM(&game->heart, HEARTS_POSITION_X + i * HEARTS_GAP_BETWEEN, HEARTS_POSITION_Y);
  }
}

void drawGameScore()
{
  MinixForce *game = getGame();

  unsigned int score = game->score;

  unsigned int ones = score % 10;
  unsigned int tens = (int)floor(score / 10) % 10;
  unsigned int hundreds = (int)floor(score / 100) % 10;
  unsigned int thousands = (int)floor(score / 1000) % 10;
  unsigned int tenthousands = (int)floor(score / 10000) % 10;

  if(game->MFstateGame  == SCORE_MENU)
  {
      /* Drawing tenthousands */
    drawXPM(&game->digits[tenthousands], SCORE_TENTHOUSANDS_POSITION_X, SCORE_TENTHOUSANDS_POSITION_Y);
    /* Drawing thousands */
    drawXPM(&game->digits[thousands], SCORE_THOUSANDS_POSITION_X, SCORE_THOUSANDS_POSITION_Y);
    /* Drawing hundreds */
    drawXPM(&game->digits[hundreds], SCORE_HUNDREDS_POSITION_X, SCORE_HUNDREDS_POSITION_Y);
    /* Drawing tens */
    drawXPM(&game->digits[tens], SCORE_TENS_POSITION_X, SCORE_TENS_POSITION_Y);
    /* Drawing ones */
    drawXPM(&game->digits[ones], SCORE_ONES_POSITION_X, SCORE_ONES_POSITION_Y);
  }
  else {
    /* Drawing tenthousands */
    drawXPM(&game->digits[tenthousands], GAME_TENTHOUSANDS_POSITION_X, GAME_TENTHOUSANDS_POSITION_Y);
    /* Drawing thousands */
    drawXPM(&game->digits[thousands], GAME_THOUSANDS_POSITION_X, GAME_THOUSANDS_POSITION_Y);
    /* Drawing hundreds */
    drawXPM(&game->digits[hundreds], GAME_HUNDREDS_POSITION_X, GAME_HUNDREDS_POSITION_Y);
    /* Drawing tens */
    drawXPM(&game->digits[tens], GAME_TENS_POSITION_X, GAME_TENS_POSITION_Y);
    /* Drawing ones */
    drawXPM(&game->digits[ones], GAME_ONES_POSITION_X, GAME_ONES_POSITION_Y);
  }


}

void drawScoreMenu()
{

  MinixForce *game = getGame();

  /* Drawing background */
  drawXPM(&game->score_menu->menuBackground, BACKGROUND_ORIGIN_COORDS, BACKGROUND_ORIGIN_COORDS);

  drawGameScore();
  drawGameTimer();
  drawEnemiesKilled();
  /* Play Button */
  if (game->MFstateScore == B_TO_MAIN)
  {
    drawXPM(&game->score_menu->backMainButton->selected, game->score_menu->backMainButton->x, game->score_menu->backMainButton->y);
  }
  else
  {
    drawXPM(&game->score_menu->backMainButton->normal, game->score_menu->backMainButton->x, game->score_menu->backMainButton->y);
  }
  /* Main Menu Button */
  if (game->MFstateScore == RESTART)
  {
    drawXPM(&game->score_menu->restartButton->selected, game->score_menu->restartButton->x, game->score_menu->restartButton->y);
  }
  else
  {
    drawXPM(&game->score_menu->restartButton->normal, game->score_menu->restartButton->x, game->score_menu->restartButton->y);
  }
  /* Quit Button */
  if (game->MFstateScore == LEAVE)
  {
    drawXPM(&game->score_menu->quitButton->selected, game->score_menu->quitButton->x, game->score_menu->quitButton->y);
  }
  else
  {
    drawXPM(&game->main_menu->quitButton->normal, game->score_menu->quitButton->x, game->score_menu->quitButton->y);
  }
}


void drawEnemiesKilled() {
  MinixForce *game = getGame();

  unsigned int enemiesKilled = game->enemiesKilled;

  unsigned int ones = enemiesKilled % 10;
  unsigned int tens = (int)floor(enemiesKilled / 10) % 10;
  unsigned int hundreds = (int)floor(enemiesKilled / 100) % 10;

  drawXPM(&game->digits[hundreds], SCORE_ENEMIES_DIG3_POSITION_X, SCORE_ENEMIES_POSITION_Y);
  drawXPM(&game->digits[tens], SCORE_ENEMIES_DIG2_POSITION_X, SCORE_ENEMIES_POSITION_Y);
  drawXPM(&game->digits[ones], SCORE_ENEMIES_DIG1_POSITION_X, SCORE_ENEMIES_POSITION_Y);
}
