#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"
#include "keyboard.h"


int keyboard_id = KEYBOARD_IRQ; 	// KEYBOARD_IRQ is defined in interrupt.h in .minix-src folder
uint32_t cnt = 0;									// counter of sys_inb calls
uint8_t scancode = 0;							// make code or break code

int (kbc_subscribe_int)(uint8_t *bit__no) {
  *bit__no = BIT(keyboard_id);
	if (sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &keyboard_id)) // this function calls sys_irqenable
		return 1;
  return 0;
}

int (kbc_unsubscribe_int)() {
	if (sys_irqrmpolicy(&keyboard_id)) // this function calls sys_irqdisable
		return 1;
  return 0;
}

int sys_inb_cnt(port_t port, uint8_t *byte) {
	uint32_t byte32;
	if(sys_inb(port, &byte32)) {
		return 1;
	}
	*byte = (uint8_t)byte32;
	cnt++;
	return 0;
}

int disable_interrupts() {
	uint8_t cmd_byte;

	if (kbc_write_command(KBC_READ_CMD)) { 	// Sends Read Command
		return 1;
	}

	if (kbc_read_out_buf(&cmd_byte)) {			// Reads Command Byte
		return 1;
	}

	cmd_byte &= !(KBC_CMD_BYTE_INT);				// Sets the Enable Interrupt Bit to 1

	if (kbc_write_command(KBC_WRITE_CMD)) {	// Sends Write Command
		return 1;
	}
	
	if (kbc_write_argument(cmd_byte)) {			// Writes Command Byte
		return 1;
	}

	return 0;
}

int enable_interrupts() {
	uint8_t cmd_byte;

	if (kbc_write_command(KBC_READ_CMD)) { 	// Sends Read Command
		return 1;
	}

	if (kbc_read_out_buf(&cmd_byte)) {			// Reads Command Byte
		return 1;
	}

	cmd_byte |= KBC_CMD_BYTE_INT;						// Sets the Enable Interrupt Bit to 1

	if (kbc_write_command(KBC_WRITE_CMD)) {	// Sends Write Command
		return 1;
	}
	
	if (kbc_write_argument(cmd_byte)) {			// Writes Command Byte
		return 1;
	}

	return 0;
}

int kbc_read_out_buf(uint8_t *content) {
	uint8_t status;

	sys_inb_cnt(STAT_REG, &status); 				// Check OUT_BUF Status:
	while (!(status & STAT_REG_OBF)) {			// IF SET READ CMD BYTE
		tickdelay(micros_to_ticks(DELAY_US)); // IF NOT SET wait for OUT_BUF to have something
		sys_inb_cnt(STAT_REG, &status);
	}

	if (status & STAT_REG_PAR || status & STAT_REG_TIMEOUT) { // Parity or Timeout error, inavlid data
		return 1;
	}

	if (sys_inb_cnt(OUT_BUF, content)) {		// Reads OUT_BUF
		return 1;
	}

	return 0;
}

int kbc_write_command(uint8_t cmd) {
	uint8_t status;

	sys_inb_cnt(STAT_REG, &status); 				// Check IN_BUF Status:
	while (status & STAT_REG_IBF) { 				// IF EMPTY write command
		tickdelay(micros_to_ticks(DELAY_US));	// IF NOT EMPTY wait for IN_BUF to be empty
		sys_inb_cnt(STAT_REG, &status);
	}

	if (status & STAT_REG_PAR || status & STAT_REG_TIMEOUT) { // Parity or Timeout error, inavlid data
		return 1;
	}
	
	if (sys_outb(KBC_CMD_REG, cmd)) { 			// Sends Command
		return 1;
	}

	return 0;
}

int kbc_write_argument(uint8_t arg) {
	uint8_t status;

	sys_inb_cnt(STAT_REG, &status); 				// Check IN_BUF Status:
	while (status & STAT_REG_IBF) { 				// IF EMPTY write argument
		tickdelay(micros_to_ticks(DELAY_US));	// IF NOT EMPTY wait for IN_BUF to be empty
		sys_inb_cnt(STAT_REG, &status);
	}

	if (status & STAT_REG_PAR || status & STAT_REG_TIMEOUT) { // Parity or Timeout error, inavlid data
		return 1;
	}

	if (sys_outb(KBC_CMD_ARG, arg)) { 			// Sends Argument
		return 1;
	}

	return 0;
}

void (kbc_ih)(void) {
	uint8_t stat;
	

	if (sys_inb_cnt(STAT_REG, &stat) != 0){
		printf("Error: Couldn't read the status\n");

		return;
	}

	// Check if OUT_BUF is empty or if there is an error
	if(!(stat & STAT_REG_OBF) || (stat & (STAT_REG_PAR|STAT_REG_TIMEOUT) )){
		return;
	}
	
	sys_inb_cnt(OUT_BUF , &scancode);
}
