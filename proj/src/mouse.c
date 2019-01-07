#include "mouse.h"

int mouse_id = KBD_AUX_IRQ;
uint8_t oneByte; // byte read from the output
struct mouse_ev evt;

int(mouse_subscribe_int)(uint16_t *bit_no) {
  *bit_no = BIT(mouse_id);
  if (sys_irqsetpolicy(KBD_AUX_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_id)) //this function calls sys_irqenable
    return 1;

  /* LCF enables stream Mode */

  //... Enabling Data Reporting

  sys_irqdisable(&mouse_id); // disable notifications

  if (kbc_write_mouse_command(MOUSE_ENA))
  { // send disable data report command
    printf("Could not disable data reporting!");
    return 1;
  }

  sys_irqenable(&mouse_id); // enable notifications

  return 0;
}

int(mouse_unsubscribe_int)() {

    //... Disabling Data Reporting
  sys_irqdisable(&mouse_id); // disable notifications

  if (kbc_write_mouse_command(MOUSE_DIS))
  {
    // send disable data report command
    printf("Could not disable data reporting!");
    return 1;
  }

  sys_irqenable(&mouse_id); // enable notifications

  //... Unsubscribing mouse interrupts
  if (sys_irqrmpolicy(&mouse_id) != 0) // this function calls sys_irqdisable
    return 1;

  return 0;
}

void(mouse_ih)() {
  mouse_read_out_buf(&oneByte);
}

int mouse_read_out_buf(uint8_t *content) {
  uint32_t status;
  uint32_t content32; // 32-bit mask for the 8-bit content
  int retry = 0;

  while (retry < 4) {
    sys_inb(STAT_REG, &status);

    //... Checking if there is any error and if the byte came from AUX
    if ((status & STAT_REG_PAR) || (status & STAT_REG_TIMEOUT) || !(status & STAT_REG_AUX)) { // Parity or Timeout error, invalid data
      return 1;
    }

    //... Checking if OUT_BUF is FULL to read
    if (status & STAT_REG_OBF) {
      //... Reading the Output Buffer
      if (sys_inb(OUT_BUF, &content32)) {
        return 1;
      }
      // The information in address content now contains content32 in 8-bit
      *content = (uint8_t) content32;
      return 0;
    }

    tickdelay(micros_to_ticks(DELAY_US)); // IF NOT EMPTY wait for IN_BUF to be empty
    retry++;
  }

  return 1;
}

int kbc_write(port_t port, uint8_t cmd) {
  uint32_t status;
  int retry = 0;

  while (retry < 4) {
    sys_inb(STAT_REG, &status);

    //... Checking if IN_BUF is OK to write to
    if (!(status & STAT_REG_IBF)) {
      //.... Writing the command
      if (sys_outb(port, cmd)) {
        return 1;
      }
      return 0;
    }

    tickdelay(micros_to_ticks(DELAY_US)); // IF NOT EMPTY wait for IN_BUF to be empty
    retry++;
  }

  return 1;
}

int kbc_write_mouse_command(uint8_t cmd) {
  uint8_t response;

  kbc_write(CTRL_REG, KBC_WRITE_MOUSE_BYTE);
  kbc_write(IN_BUF, cmd);
  tickdelay(micros_to_ticks(DELAY_US));
  mouse_read_out_buf(&response);

  // Checking if invalid byte
  if (response != ACK) {
    // repeat process if invalid
    kbc_write(CTRL_REG, KBC_WRITE_MOUSE_BYTE);
    kbc_write(IN_BUF, cmd);
    tickdelay(micros_to_ticks(DELAY_US));
    mouse_read_out_buf(&response);
    // Checking if second consecutive invalid byte
    if (response == ERROR)
      return 1;
  }

  return 0;
}

int mouse_parse_packet(struct packet *pp) {
  
  //... Checking X Coordinate Sign
  if (pp->bytes[0] & MOUSE_X_SIGN) {
    pp->delta_x = -pp->bytes[1];
    pp->delta_x ^= 0xFF;
    pp->delta_x += 1;
  }
  else {
    pp->delta_x = pp->bytes[1];
  }

  //... Checking Y Coordinate Sign
  if (pp->bytes[0] & MOUSE_Y_SIGN) {
    pp->delta_y = -pp->bytes[2];
    pp->delta_y ^= 0xFF;
    pp->delta_y += 1;
  }
  else {
    pp->delta_y = pp->bytes[2];
  }

  //... Checking coordinates overflow
  if (pp->bytes[0] & MOUSE_X_OVFL) { // X Coordinate
    pp->x_ov = true;
  }
  else {
    pp->x_ov = false;
  }

  if (pp->bytes[0] & MOUSE_Y_OVFL) { // Y Coordinate
    pp->y_ov = true;
  }
  else {
    pp->y_ov = false;
  }

  //... Checking mouse buttons
  if (pp->bytes[0] & MOUSE_LB) { // Left Button
    pp->lb = true;
  }
  else {
    pp->lb = false;
  }

  if (pp->bytes[0] & MOUSE_RB) { // Right Button
    pp->rb = true;
  }
  else {
    pp->rb = false;
  }

  if (pp->bytes[0] & MOUSE_MB) { // Middle Button
    pp->mb = true;
  }
  else {
    pp->mb = false;
  }
  return 0;
}

void weapon(struct packet *pp) {
 
  MinixForce* game = getGame();
  if (mouse_parse_packet(pp)) // receive the status of mouse
    return;

  struct mouse_ev *event = mouse_detect_event(pp);

  if (event->type == LB_PRESSED) {   
    updateMouseState(FIRE);
    game->MFstateMouse = FIRE;
  }
  if (event->type == MOUSE_MOV) {
    updateMouse(pp);
  }
  return; 
}

void updateMouse(struct packet *pp) {

  MinixForce* game = getGame();
  /* Checking if overflow */
  if (pp->x_ov)
    return;
  if (pp->y_ov)
    return;

  int newX = game->crosshair->x + pp->delta_x;
  int newY = game->crosshair->y - pp->delta_y;
  int crosshairWidth = game->crosshair->aim.width;
  int crosshairHeight = game->crosshair->aim.height;

  /* Checking if mouse is within the borders */
  /* X coordinate */
  if (newX < 0) { 
    game->crosshair->x = 0;
  }
  else if (newX > (int)get_hres() - crosshairWidth) {
    game->crosshair->x = get_hres() - crosshairWidth;
  }
  else
    game->crosshair->x = newX;

  /* Y coordinate */
  if (newY < 100) { 
    game->crosshair->y = 100;
  }
  else if (newY > (int)get_vres() - crosshairHeight) {
    game->crosshair->y = get_vres() - crosshairHeight;
  }
  else
    game->crosshair->y = newY;
}

uint32_t getmouse_id(){
  return (uint32_t)mouse_id;
}

uint8_t getoneByte(){
  return oneByte;
}
