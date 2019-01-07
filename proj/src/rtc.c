#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "mrtc.h"
#include "rtc.h"
#include "minixforce.h"

int hook___id = RTC_IRQ; // hook_id = 0

int rtc_subscribe_int(uint8_t *bit_no_)
{
	clear_regC();
	enable_interrupts_();
	*bit_no_ = BIT(hook___id);
	if (sys_irqsetpolicy(RTC_IRQ, IRQ_EXCLUSIVE | IRQ_REENABLE, &hook___id) != OK) //this function calls sys_irqenable
		return 1;
	return 0;
}

int rtc_unsubscribe_int ()
{
	clear_regC();
	disable_interrupts_();
	if (sys_irqrmpolicy(&hook___id) != OK) //this function calls sys_irqdisable
		return 1;
	return 0;
}

int isValid_rtc(){
	uint32_t regA;
	sys_outb(RTC_ADDR_REG, RTC_REG_A);
	sys_inb(RTC_DATA_REG, &regA);
	//return 1 if not valid and 0 if valid
	return (!(RTC_UIP & regA));
} 

void clear_regC(){
	uint32_t regC;
	sys_outb(RTC_ADDR_REG, RTC_REG_C);
	sys_inb(RTC_DATA_REG, &regC);
}

void enable_interrupts_(){

	uint32_t aux11;
	sys_outb(RTC_ADDR_REG, RTC_REG_B);
	sys_inb(RTC_DATA_REG, &aux11);
	
	aux11 &= ~BIT(5); // unset set bit 5 -- PIE (periodic)
	aux11 &= ~BIT(6); // unset set bit 6 -- AIE (alarm)
	aux11 |= BIT(4); // set bit 4 -- UIE (update done)

	sys_outb(RTC_ADDR_REG, RTC_REG_B);
	sys_outb(RTC_DATA_REG, aux11);
	
}

void disable_interrupts_(){
	uint32_t aux22;
	sys_outb(RTC_ADDR_REG, RTC_REG_B);
	sys_inb(RTC_DATA_REG, &aux22);
	aux22 &= ~BIT(4); // unset bit 4 -- UIE (update done)
	sys_outb(RTC_ADDR_REG, RTC_REG_B);
	sys_outb(RTC_DATA_REG, aux22);
}


int bcd_to_decimal(uint32_t x) {
    return x - 6 * (x >> 4);
}

void rtc_Date(){
	MinixForce *game = getGame();
	uint32_t aux9, aux91, aux92;
	sys_outb(RTC_ADDR_REG, RTC_DAYOFMONTH);
	sys_inb(RTC_DATA_REG, &aux9);
	game->real_time->day = bcd_to_decimal( aux9);

	sys_outb(RTC_ADDR_REG, RTC_MONTH);
	sys_inb(RTC_DATA_REG, &aux91);
	game->real_time->month = bcd_to_decimal( aux91);

	sys_outb(RTC_ADDR_REG, RTC_YEAR);
	sys_inb(RTC_DATA_REG, &aux92);
	game->real_time->year = bcd_to_decimal(aux92) + MILLENUIM; //works in the next 981 years
}
void rtc_Time(){

	MinixForce *game = getGame();
	
	uint32_t aux93, aux94, aux95;
	
	sys_outb(RTC_ADDR_REG, RTC_SECONDS);
	sys_inb(RTC_DATA_REG, &aux93);
	game->real_time->sec = bcd_to_decimal( aux93);
	

	sys_outb(RTC_ADDR_REG, RTC_MINUTES);
	sys_inb(RTC_DATA_REG, &aux94);
	game->real_time->min = bcd_to_decimal( aux94);

	sys_outb(RTC_ADDR_REG, RTC_HOURS);
	sys_inb(RTC_DATA_REG, &aux95);
	game->real_time->hour = bcd_to_decimal( aux95);
}

void rtc_ih()
{
	do{
		if(isValid_rtc()){
			rtc_Date();
			rtc_Time();
		}		
	} while (!isValid_rtc());

}

int rtc_test_conf()
{
  uint32_t regA = 0, regB = 0, regC = 0, regD = 0;

  // wait_valid_rtc();

  sys_outb(RTC_ADDR_REG, RTC_REG_A);

  sys_inb(RTC_DATA_REG, &regA);

  sys_outb(RTC_ADDR_REG, RTC_REG_B);

  sys_inb(RTC_DATA_REG, &regB);

  sys_outb(RTC_ADDR_REG, RTC_REG_C);

  sys_inb(RTC_DATA_REG, &regC);

  sys_outb(RTC_ADDR_REG, RTC_REG_D);

  sys_inb(RTC_DATA_REG, &regD);

  return 0;

}
