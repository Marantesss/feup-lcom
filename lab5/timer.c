#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

unsigned int counter = 0; // Initializing counter to 0
int hook_id = TIMER0_IRQ; // hook_id = 0

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  // The maximum value of a 16 bit number is 65535, so, because (freq=TIMER_IRQ/div), freq needs to be higher than 19
  if (freq < 19) {
    printf("ERROR! Frequency set too low!\n");
    return 1;
  }
  // TIMER_FREQ = freq / div so...
  uint16_t div = (uint16_t) (TIMER_FREQ / freq);

  // Defining the MSB and LSB variables
  uint8_t msb, lsb;
  util_get_LSB(div, &lsb);
  util_get_MSB(div, &msb);
  uint8_t st;
  if(timer_get_conf(timer, &st) == 1) //op fail
    return 1;
  // Choosing which timer to get config from
  if (timer == 0) { // Timer 0
    st = (uint8_t) ((st & 0x0f) | TIMER_LSB_MSB | TIMER_SEL0); // To not change the 4 LSBs (mask 0x0f = 0000 1111)
    sys_outb(TIMER_CTRL, st); // Sending the control word to program the timer
    // Programming the timer    
    sys_outb(TIMER_0, lsb);
    sys_outb(TIMER_0, msb);
  }
  else if (timer == 1) { // Timer 1
    st = (uint8_t) ((st & 0x0f) | TIMER_LSB_MSB | TIMER_SEL1); // To not change the 4 LSBs (mask 0x0f = 0000 1111)
    sys_outb(TIMER_CTRL, st); // Sending the control word to program the timer
    // Programming the timer    
    sys_outb(TIMER_1, lsb);
    sys_outb(TIMER_1, msb);
  }
  else if (timer == 2) { // Timer 2
    st = (uint8_t) ((st & 0x0f) | TIMER_LSB_MSB | TIMER_SEL2); // To not change the 4 LSBs (mask 0x0f = 0000 1111)
    sys_outb(TIMER_CTRL, st); // Sending the control word to program the timer
    // Programming the timer    
    sys_outb(TIMER_2, lsb);
    sys_outb(TIMER_2, msb);
  }
  else {  // Invalid timer
    return 1;
  }
  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  *bit_no = BIT(hook_id);
	if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id) != OK) //this function calls sys_irqenable
		return 1;
  return 0;
}

int (timer_unsubscribe_int)() {
	if (sys_irqrmpolicy(&hook_id) != OK) //this function calls sys_irqdisable
		return 1;
  return 0;
}

void (timer_int_handler)() {
  counter++; //add 1 to counter
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint32_t config;

  // Making the Read Back Command to get config
  uint8_t rb = TIMER_RB_CMD; // 1100 0000
  rb |= TIMER_RB_COUNT_; // 1110 0000
  rb |= TIMER_RB_SEL(timer);
  // Choosing which timer to get config from
  if (timer == 0) { // Timer 0
    sys_outb(TIMER_CTRL, rb);
    sys_inb(TIMER_0, &config);
  }
  else if (timer == 1) { // Timer 1
    sys_outb(TIMER_CTRL, rb);
    sys_inb(TIMER_1, &config);
  }
  else if (timer == 2) { // Timer 2
    sys_outb(TIMER_CTRL, rb);
    sys_inb(TIMER_2, &config);
  }
  else { // Invalid timer
    return 1;
  }
  *st = (unsigned char)config;
  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  union timer_status_field_val conf;
  if (field == all) {
    conf.byte = st;
  }
  else if (field == initial) {
    // Checking Initialization Mode (0x30 - 0011 0000)
    if ((st & 0x30) == TIMER_LSB) { // LSB - 0001 0000
      conf.in_mode = LSB_only;
    }
    else if ((st & 0x30) == TIMER_MSB) { // MSB - 0010 0000
      conf.in_mode = MSB_only;
    }
    else if ((st & 0x30) == TIMER_LSB_MSB) { // LSB followed by MSB - 0011 0000
      conf.in_mode = MSB_after_LSB;
    }
    else { // Invalid Initialization Mode
      conf.in_mode = INVAL_val;
      return 1;
    }
  }
  else if (field == mode) {
    // Checking Counting Mode (0x0E - 0000 1110, 0x06 - 0000 0110)
    if ((st & 0x0E) == 0) { // Mode 0 - 0000
      conf.count_mode = 0;
    }
    else if ((st & 0x0E) == BIT(1)) { // Mode 1 - 0010
      conf.count_mode = 1;
    }
    else if ((st & 0x06) == TIMER_RATE_GEN) { // Mode 2 - 0100 or 1100
      conf.count_mode = 2;
    }
    else if ((st & 0x06) == TIMER_SQR_WAVE) { // Mode 3 - 1110 or 0110
      conf.count_mode = 3;
    }
    else if ((st & 0x0E) == BIT(3)) { // Mode 4 - 1000
      conf.count_mode = 4;
    }
    else if ((st & 0x0E) == (BIT(3) | BIT(1))) { // Mode 5 - 1010
      conf.count_mode = 5;
    }
    else { // Invalid Counting Mode
      printf("ERROR: Invalid Counting Mode!\n");
      return 1;
    }
  }
  else if (field == base) {
    // Checking Counting Base
    if ((st & 0x01) == TIMER_BIN) { // Binary Base - 0000
      conf.bcd = false;
    }
    else if ((st & 0x01) == TIMER_BCD) { // BCD Base - 0001
      conf.bcd = true;
    }
    else { // Invalid Base
      return 1;
    }
  }
  else { // Invalid field
    return 1;
  }
  timer_print_config(timer, field, conf); // Printing the timers config

  return 0;
}
