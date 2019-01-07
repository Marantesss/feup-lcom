#include "interrupts.h"

uint8_t keyboardirq, timerirq, rtcirq;
uint16_t mouseirq;

int subscribes()
{

  if (timer_subscribe_int(&timerirq))
  { // Check if subscription worked
    printf("Could not subscribe timer irq!\n");
    return 1;
  }
  if (kbc_subscribe_int(&keyboardirq))
  { // Check if subscription worked
    printf("Could not subscribe Keyboard \n");
    return 1;
  }

  //... Subscribing Mouse Interrupts
  if (mouse_subscribe_int(&mouseirq))
  { // Check if subscription worked
    printf("Could not subscribe Mouse!\n");
    return 1;
  }

  if (rtc_subscribe_int(&rtcirq))
  { // Check if subscription worked
    printf("Could not subscribe rtc!\n");
    return 1;
  }

  return 0;
}

int unsubscribes()
{

  if (timer_unsubscribe_int())
  { // Check if subscription worked
    printf("Could not unsubscribe timer irq!\n");
    return 1;
  }

  if (kbc_unsubscribe_int())
  { // Check if subscription worked
    printf("Could not unsubscribe Keyboard \n");
    return 1;
  }

  if (mouse_unsubscribe_int())
  { // Check if subscription worked
    printf("Could not unsubscribe Mouse!\n");
    return 1;
  }

  if (rtc_unsubscribe_int())
  {
    printf("Could not unsubscribe RTC!\n");
    return 1;
  }
  return 0;
}

void interruptHandler()
{

  MinixForce *game = getGame();

  if (game->MFstateGame == MAIN_MENU)
  {
    main_menu_IH();
  }
  //help menu and pause menu are direct to the same interrupt handler
  else if (game->MFstateGame == HELP_MENU || game->MFstateGame == PAUSE_MENU)
  {
    help_pause_IH();
  }
  else if (game->MFstateGame == GAME)
  {
    IHgame();
  }
  else if (game->MFstateGame == SCORE_MENU)
  {
    IHend();
  }
  else if (game->MFstateGame == COUNT_DOWN)
  {
    IHcount();
  }
}

void IHcount()
{
  int r, ipc_status;
  message msg;

  bool end = false;
  while (!end)
  { // loop until the caracter dies

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
    {
      printf("driver_receive failed with: %d!", r);
      continue;
    }

    if (is_ipc_notify(ipc_status))
    { // received notification
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE: // hardware interrupt notification
        //removes from the buffer mouse status informations
        if (msg.m_notify.interrupts & mouseirq)
        { // subscribed interrupt
          mouse_ih();
          break;
        }    
        //removes from the buffer keyboard status informations      
        if (msg.m_notify.interrupts & keyboardirq)
        {           // subscribed interrupt
          kbc_ih(); //keyboard handler
          break;
        }
  
        if (msg.m_notify.interrupts & timerirq)
        { // dealing with the interruption call
          end = true;
          break;
        }

      default:
        break; // no other notifications expected: do nothing
      }
    }
  }
}

void IHend()
{
  MinixForce *game = getGame();
  int r, ipc_status;
  message msg;

  /* keyboard */
  bool continuar = false;  //flag for interruption
  uint8_t size, bytes[2];  //size can be of one or two bytes

  bool end = false;

  while (!end)
  { // loop until the caracter dies
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
    {
      printf("driver_receive failed with: %d!", r);
      continue;
    }
    if (is_ipc_notify(ipc_status))
    { // received notification
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE: // hardware interrupt notification

        if (msg.m_notify.interrupts & keyboardirq)
        {           // subscribed interrupt
          kbc_ih(); //keyboard handler

          if (continuar)
          {
            bytes[1] = getScancode(); // Add second byte to the array
            continuar = false;
          }
          else if (getScancode() == TWO_BYTE_SCANCODE)
          { // 3 - Scancode is 2-byte
            size = 2;
            bytes[0] = getScancode();
            continuar = true; // Add first byte to the array
                              //can only remove one code for the buffer so 2 byte will be removed in another call
          }
          else
          { // 3 - Scancode is 1-byte
            size = 1;
            bytes[0] = getScancode(); // Add scancode to the array
            continuar = false;   //already remove everything from the buffer to print the code
          }
          if (!continuar)
          {
            if (size == 1 && getScancode() == MAKE_ENTER)
            {
              if (game->MFstateScore == RESTART || game->MFstateScore == B_TO_MAIN)
              {
                restartMinixForce();
              }
              updateScoreState(ENTER);
            }

            else if (size == 2 && getScancode() == MAKE_DOWN)
            {
              updateScoreState(KDOWN);
            }
            else if (size == 2 && getScancode() == MAKE_UP)
            {
              updateScoreState(KUP);
            }
            end = true;
          }

          break;
        }
        //removes from the buffer mouse status informations
        if (msg.m_notify.interrupts & mouseirq)
        { // subscribed interrupt
          mouse_ih();
          end = true;
          break;
        }
      default:
        break; // no other notifications expected: do nothing
      }
    }
  }
}

void main_menu_IH()
{
  int r, ipc_status;
  message msg;

  /* keyboard */
  bool continuar = false;  //flag for interruption
  uint8_t size, bytes[2];  //size can be of one or two bytes

  bool end = false;

  while (!end)
  { // loop until the caracter dies

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
    {
      printf("driver_receive failed with: %d!", r);
      continue;
    }

    if (is_ipc_notify(ipc_status))
    { // received notification
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE: // hardware interrupt notification

        if (msg.m_notify.interrupts & keyboardirq)
        { // subscribed interrupt

          kbc_ih(); //keyboard handler

          if (continuar)
          {
            bytes[1] = getScancode(); // Add second byte to the array
            continuar = false;
          }

          else if (getScancode() == TWO_BYTE_SCANCODE)
          { // 3 - Scancode is 2-byte
            size = 2;
            bytes[0] = getScancode();
            continuar = true; // Add first byte to the array
            //can only remove one code for the buffer so 2 byte will be removed in another call
          }

          else
          { // 3 - Scancode is 1-byte

            size = 1;
            bytes[0] = getScancode(); // Add scancode to the array
            continuar = false;   //already remove everything from the buffer to print the code
          }

          if (!continuar)
          {
            if (size == 1 && getScancode()== MAKE_ENTER)
            {
              updateMainState(ENTER);
            }

            if (size == 2 && getScancode() == MAKE_DOWN)
            {
              updateMainState(KDOWN);
            }

            if (size == 2 && getScancode() == MAKE_UP)
            {
              updateMainState(KUP);
            }
            end = true;
          }

          break;
        }
        //to the keyboard don't stop movement
        if (msg.m_notify.interrupts & mouseirq)
        { // subscribed interrupt
          mouse_ih();
          break;
        }

        if (msg.m_notify.interrupts & timerirq)
        { // dealing with the interruption call
          end = true;
          break;
        }
      default:
        break; // no other notifications expected: do nothing
      }
    }
    else
    { // received a standard message, not a notification
      // no standard messages expected: do nothing
    }
  }
  return;
}

void IHgame()
{
  MinixForce *game = getGame();
  int r, ipc_status;
  message msg;

  /*keyboard */
  uint8_t bytes[1];        //size can be of one or two bytes

  /* mouse  */
  struct packet p;             // packet with 3 bytes
  unsigned int byteNumber = 0; // counts the number of bytes read
  bool end = false;

  while (!end)
  { // loop until the caracter dies
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
    {
      printf("driver_receive failed with: %d!", r);
      continue;
    }
    if (is_ipc_notify(ipc_status))
    { // received notification
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE:
        if (msg.m_notify.interrupts & mouseirq)
        { // subscribed interrupt
          mouse_ih();
          //must read only one byte
          if ((byteNumber == 0 && (BIT(3) & getoneByte())) || byteNumber == 1 || byteNumber == 2)
          {                                //access the struct bytes
            p.bytes[byteNumber] = getoneByte(); // bytes 0, 1 or 2
            byteNumber++;                  // increments the counter to know in the next interrupt
          }

          if (byteNumber == 3)
          {                 // 3 bytes haven been read and there's no error
            byteNumber = 0; // reset to start counting new packets
            weapon(&p);     //function that change weapon stage
            end = true;
          }

          break;
        }
        if (msg.m_notify.interrupts & keyboardirq)
        {                      // subscribed interrupt
          kbc_ih();            //keyboard handler
          bytes[0] = getScancode(); // Add scancode to the array
          //player goes back
          if (bytes[0] == MAKE_A)
          {
            updatePlayerState(BACK);
            end = true;
          }
          //player goes front
          else if (bytes[0] == MAKE_D)
          {
            updatePlayerState(FRONT);
            end = true;
          }
          //player goes up
          else if (bytes[0]== MAKE_W)
          {
            updatePlayerState(PUP);
            end = true;
          }
          //player goes down
          else if (bytes[0] == MAKE_S)
          {
            updatePlayerState(PDOWN);
            end = true;
          }
          //pause the game
          else if (bytes[0] == BREAK_SPACE)
          {
            updateGameState(PAUSE);
            end = true;
          }
          //leaves the game, going to score menu
          else if (bytes[0] == MAKE_ESC)
          {
            game->MFstateGame = SCORE_MENU;
            updateGameState(SCORE);
            end = true;
          }
          break;
        }

        if (msg.m_notify.interrupts & timerirq)
        {
          //counts the time playing that game
          game->time_alive++;
          game->time_ticket = 1;
          //if its called in were, the movement is constant
          updateZombiesPositions();
          end = true;
          break;
        }

      default:
        break; // no other notifications expected: do nothing
      }
    }
  }
  return;
}

void help_pause_IH()
{
  //gets the game
  MinixForce *game = getGame();
  int r, ipc_status;
  message msg;
  bool key = true;

  /* keyboard */
  uint8_t bytes[1];        //size can be of one or two bytes

  while (key)
  { // loop until the caracter dies
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
    {
      printf("driver_receive failed with: %d!", r);
      continue;
    }
    if (is_ipc_notify(ipc_status))
    { // received notification
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE: // hardware interrupt notification

        if (msg.m_notify.interrupts & keyboardirq)
        {                      // subscribed interrupt
          kbc_ih();            //keyboard handler
          bytes[0] = getScancode(); // Add scancode to the array
          //if we are in the help menu and press esc, leave to main
          if (game->MFstateGame == HELP_MENU && getScancode() == ESC_BREAKCODE)
          {
            updateGameState(MAIN);
            key = false;
          }
          //if we are in pause and press break, continue game
          else if (game->MFstateGame == PAUSE_MENU && getScancode() == BREAK_SPACE)
          {
            //Status of the game GAME, with the event SPLAYER
            updateGameState(COUNT);
            key = false;
          }
          break;
        }
        //only gets onformation of the buffer, because the keyboard uses the same buffer
        if (msg.m_notify.interrupts & mouseirq)
        { // subscribed interrupt
          mouse_ih();
          break;
        }
        if (msg.m_notify.interrupts & timerirq)
        {
          if (game->MFstateGame == HELP_MENU ){
            //counts the time playing that game
           game->time_ticket = 1;
           game->time_alive++;
           key = false;
          }
          break;
        }

      default:
        break; // no other notifications expected: do nothing
      }
    }
  }

  return;
}
