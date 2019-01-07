// IMPORTANT: you must include the following line in all your C files
// Any header files included below this line should have been created by you
#include <lcom/lcf.h>

#include "i8042.h"
#include "i8254.h"
#include "keyboard.h"
#include "macros.h"
#include "video_gr.h"
#include "sprite.h"

int main(int argc, char *argv[])
{
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay)
{
  // changing to the specified video mode
  if(vg_init(mode) == NULL)
    return 1;

  // waiting for the specified time
  sleep(delay);

  //resets the video controller to operate in text mode
  vg_exit();

  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color)
{
  uint8_t size, bytes[2]; //size can be of one or two bytes
  bool make = false;      //make or break code
  int r, ipc_status;
  message msg;
  bool continuar = false; //flag for interruption
  uint8_t keyboardirq;
  extern uint8_t scancode; // make code or break code

  if (kbc_subscribe_int(&keyboardirq) == 1)
  { // Check if subscription worked
    printf("Could not subscribe Keyboard \n");
    return 1;
  }

  // changing to the specified video mode
  if(vg_init(mode) == NULL)
    return 1;

  //desenha retangulos
  vg_draw_rectangle(x, y, width, height, color);

  while (scancode != ESC_BREAKCODE)
  { // function should exit when the user releases the Esc key
    /*Get a request message.*/

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
    {
      printf("ERROR: driver_receive failed with: %d", r);
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
            bytes[1] = scancode; // Add second byte to the array
            continuar = false;
          }
          else if (scancode == TWO_BYTE_SCANCODE)
          { // 3 - Scancode is 2-byte
            size = 2;
            bytes[0] = scancode;
            continuar = true; // Add first byte to the array
                              //can only remove one code for the buffer so 2 byte will be removed in another call
          }
          else
          { // 3 - Scancode is 1-byte
            size = 1;
            bytes[0] = scancode; // Add scancode to the array
            continuar = false;   //already remove everything from the buffer to print the code
          }
          if (!continuar)
          {
            if (scancode & MAKE_CODE)
            {               // 4 - Checks if code is make or break
              make = false; //break code
            }
            else
            {
              make = true; //make code
            }
          }
        }
        break;
      default:
        break; // no other notifications expected: do nothing
      }
    }
    else
    { // received a standard message, not a notification
      // no standard messages expected: do nothing
    }
  }

  //resets the video controller to operate in text mode
  vg_exit();

  if (kbc_unsubscribe_int() == 1)
  { // Check if subscription worked
    printf("Could not unsubscribe Keyboard \n");
    return 1;
  }

  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step)
{
  uint8_t keyboardirq;
  extern uint8_t scancode; // make code or break code
  uint8_t size, bytes[2];  //size can be of one or two bytes
  bool make = false;       //make or break code
  int r, ipc_status;
  message msg;
  bool continuar = false; //flag for interruption

  if (kbc_subscribe_int(&keyboardirq) == 1)
  { // Check if subscription worked
    printf("Could not subscribe Keyboard \n");
    return 1;
  }

  // changing to the specified video mode
  if (vg_init(mode) == NULL)
    return 1;

  //length of each rectangle
  int hLen = (get_hres() / no_rectangles);

  //width of each rectangle
  int vLen = (get_vres() / no_rectangles);
  uint32_t coll;

  int y = 0;
  for (unsigned int i = 0; i < no_rectangles; i++)
  {
    int x = 0;

    for (unsigned int j = 0; j < no_rectangles; j++)
    {
      coll = next_color(no_rectangles, j, i, first, step);
      vg_draw_rectangle(x, y, hLen, vLen, coll);
      x += hLen;
    }
    y += vLen;
  }

  while (scancode != ESC_BREAKCODE)
  {
    // function should exit when the user releases the Esc key
    /*Get a request message.*/
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
    {
      printf("ERROR: driver_receive failed with: %d", r);
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
            bytes[1] = scancode; // Add second byte to the array
            continuar = false;
          }
          else if (scancode == TWO_BYTE_SCANCODE)
          { // 3 - Scancode is 2-byte
            size = 2;
            bytes[0] = scancode;
            continuar = true; // Add first byte to the array
            //can only remove one code for the buffer so 2 byte will be removed in another call
          }
          else
          { // 3 - Scancode is 1-byte
            size = 1;
            bytes[0] = scancode; // Add scancode to the array
            continuar = false;   //already remove everything from the buffer to print the code
          }
          if (!continuar)
          {
            if (scancode & MAKE_CODE)
            {               // 4 - Checks if code is make or break
              make = false; //break code
            }
            else
            {
              make = true; //make code
            }
          }
        }
        break;
      default:
        break; // no other notifications expected: do nothing
      }
    }
    else
    { // received a standard message, not a notification
      // no standard messages expected: do nothing
    }
  }

  //resets the video controller to operate in text mode
  vg_exit();

  if (kbc_unsubscribe_int() == 1)
  { // Check if subscription worked
    printf("Could not unsubscribe Keyboard \n");
    return 1;
  }

  return 0;
}

//xpm	array with XPM (assuming indexed color mode)
int(video_test_xpm)(const char *xpm[], uint16_t x, uint16_t y)
{
  //change to video mode 0x105
  if (vg_init(VBE_GRAPHIC_1) == NULL)
    return 1;

  int width = 0;
  int height = 0;

  char *xpm_mem = read_xpm(xpm, &width, &height);

  draw_xpm(xpm_mem, width, height, x, y);

  // to test
  // sleep(2);

  vg_exit();

  return 0;
}

int(video_test_move)(const char *xpm[], uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf, int16_t speed, uint8_t fr_rate)
{
  uint8_t keyboardirq;
  extern uint8_t scancode; // make code or break code
  uint8_t size, bytes[2];  //size can be of one or two bytes
  bool make = false;       //make or break code
  int r, ipc_status;
  message msg;
  bool continuar = false; //flag for interruption
  uint8_t timerirq;
  extern unsigned int counter;
  bool erro = false;
  // uint16_t movement;

  if (fr_rate > 60)
  {
    printf("Framerate should be inferior to 60 fps\n");
    return 1;
  }

  //... Changing to video mode 0x105
  if (vg_init(VBE_GRAPHIC_1) == NULL)
  {
    return 1;
  }

  // subscribing keyboard interrupts
  if (kbc_subscribe_int(&keyboardirq) == 1)
  { // Check if subscription worked
    printf("Could not subscribe Keyboard \n");
    return 1;
  }

  if (timer_subscribe_int(&timerirq) == 1)
  { // Check if subscription worked
    printf("Could not subscribe timer irq!\n");
    return 1;
  }
  uint16_t x = abs(xf - xi);
  uint16_t y = abs(yf - yi);
  uint16_t xspeed = 0, yspeed = 0;
  //number of pixels between consecutive frames
  if (y > 0 && x == 0) {
    if (yf < yi)
      yspeed = -abs(speed);
    else
      yspeed = abs(speed);
  }
  else if (x > 0 && abs(yf - yi) == 0) {
    if (xf < xi)
      xspeed = -abs(speed);
    else
      xspeed = abs(speed);
  }
  else
  {
    erro = true;
  }
  if (!erro)
  {
    Sprite *sprite = create_Sprite(xpm, xi, yi, xspeed, yspeed);

    // function should exit when the user releases the Esc key
    while (scancode != ESC_BREAKCODE)
    {

        // Get a request message
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
          printf("ERROR: driver_receive failed with: %d", r);
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
                bytes[1] = scancode; // Add second byte to the array
                continuar = false;
              }
              else if (scancode == TWO_BYTE_SCANCODE)
              { // 3 - Scancode is 2-byte
                size = 2;
                bytes[0] = scancode;
                continuar = true; // Add first byte to the array
                //can only remove one code for the buffer so 2 byte will be removed in another call
              }
              else
              { // 3 - Scancode is 1-byte
                size = 1;
                bytes[0] = scancode; // Add scancode to the array
                continuar = false;   //already remove everything from the buffer to print the code
              }
              if (!continuar)
              {
                if (scancode & MAKE_CODE)
                {               // 4 - Checks if code is make or break
                  make = false; //break code
                }
                else
                {
                  make = true; //make code
                }
              }
            }
            if (msg.m_notify.interrupts & timerirq) {
              timer_int_handler();
              if (sprite->x != xf || sprite->y != yf) {
                    if (speed > 0 && (counter % (FREQ / fr_rate)) % abs(speed) == 0) {
                  clear_video_mem();
                  animate_Sprite(sprite);
                }
                else if (speed < 0 && (counter % (FREQ / fr_rate)) == 0) {
                  clear_video_mem();
                  animate_Sprite(sprite);
                }

                /*
                if (speed > 0 && (counter * fr_rate) % FREQ == 0) {
                  clear_video_mem();
                  animate_Sprite(sprite);
                }
                else if (speed < 0 && (counter / fr_rate) % FREQ == 0) {
                  clear_video_mem();
                  animate_Sprite(sprite);
                }
                */
              }
            }
            break;
          default:
            break; // no other notifications expected: do nothing
          }
        }
        else
        { // received a standard message, not a notification
          // no standard messages expected: do nothing
        }
    }

    destroy_Sprite(sprite);
  }

  //resets the video controller to operate in text mode
  vg_exit();

  if (kbc_unsubscribe_int() == 1)
  { // Check if subscription worked
    printf("Could not unsubscribe Keyboard!\n");
    return 1;
  }

  return 0;
  if (timer_unsubscribe_int() == 1)
  { //op failed
    printf("Could not unsubscribe Timer!\n");
    return 1;
  }
}


int (video_test_controller)(){
   
  vg_vbe_contr_info_t vbe_info;

  vbe_get_info(&vbe_info);

  vg_display_vbe_contr_info(&vbe_info);

  return 0;
}
