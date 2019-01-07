#include <lcom/lcf.h>
#include <lcom/timer.h>
#include <stdint.h>

#include "i8254.h"

int hook_id = TIMER0_IRQ; // hook_id = 0

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

