#include "keyboard.h"

int keyboard_id = KEYBOARD_IRQ; 	// KEYBOARD_IRQ is defined in interrupt.h in .minix-src folder
uint32_t scancode = 0;						// make code or break code

int (kbc_subscribe_int)(uint8_t *bit__no) {
  *bit__no = BIT(keyboard_id);
	if (sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &keyboard_id)) // this function calls sys_irqenable
		return -1;
  return 0;
}

int (kbc_unsubscribe_int)() {
	if (sys_irqrmpolicy(&keyboard_id)) // this function calls sys_irqdisable
		return 1;
  return 0;
}

int disable_interrupts() {
	uint32_t cmd_byte;

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
	uint32_t cmd_byte;

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

int kbc_read_out_buf(uint32_t *content) {
	uint32_t status;

	sys_inb(STAT_REG, &status); 						// Check OUT_BUF Status:
	while (!(status & STAT_REG_OBF)) {			// IF SET READ CMD BYTE
		tickdelay(micros_to_ticks(DELAY_US)); // IF NOT SET wait for OUT_BUF to have something
		sys_inb(STAT_REG, &status);
	}

	if (status & STAT_REG_PAR || status & STAT_REG_TIMEOUT) { // Parity or Timeout error, inavlid data
		return 1;
	}

	if (sys_inb(OUT_BUF, content)) {		// Reads OUT_BUF
		return 1;
	}

	return 0;
}

int kbc_write_command(uint32_t cmd) {
	uint32_t status;

	sys_inb(STAT_REG, &status); 				// Check IN_BUF Status:
	while (status & STAT_REG_IBF) { 				// IF EMPTY write command
		tickdelay(micros_to_ticks(DELAY_US));	// IF NOT EMPTY wait for IN_BUF to be empty
		sys_inb(STAT_REG, &status);
	}

	if (status & STAT_REG_PAR || status & STAT_REG_TIMEOUT) { // Parity or Timeout error, inavlid data
		return 1;
	}	
	
	if (sys_outb(STAT_REG, cmd)) { 			// Sends Command
		return 1;
	}

	return 0;
}

int kbc_write_argument(uint32_t arg) {
	uint32_t status;

	sys_inb(STAT_REG, &status); 				// Check IN_BUF Status:
	while (status & STAT_REG_IBF) { 				// IF EMPTY write argument
		tickdelay(micros_to_ticks(DELAY_US));	// IF NOT EMPTY wait for IN_BUF to be empty
		sys_inb(STAT_REG, &status);
	}

	if (status & STAT_REG_PAR || status & STAT_REG_TIMEOUT) { // Parity or Timeout error, inavlid data
		return 1;
	}

	if (sys_outb(IN_BUF, arg)) { 			// Sends Argument
		return 1;
	}

	return 0;
}

void (kbc_ih)(void) {
	uint32_t status;
	
	
	if (sys_inb(STAT_REG, &status) != 0){
		printf("Error: Couldn't read the status\n");

		return;
	}

	// Check if OUT_BUF is empty or if there is an error
	if(!(status & STAT_REG_OBF) || (status & (STAT_REG_PAR|STAT_REG_TIMEOUT) )){
		return;
	}
	
	sys_inb(OUT_BUF , &scancode);
}

uint8_t getScancode()
{
	return (uint8_t)scancode;
}
