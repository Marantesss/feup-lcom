#include <lcom/timer.h>
#include <lcom/lcf.h> //possui a funcao kbd_print_scancode

#include <stdbool.h>
#include <stdint.h>
#include <minix/sysutil.h>
#include "keyboard.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

unsigned int counter;     //counts the time
uint8_t keyboardirq ;      
extern uint32_t cnt; 			// Extern allows to access "cnt" varaible in keyboard.c
extern uint8_t scancode;	// make code or break code

int (kbd_test_scan)(bool assembly) {
	uint8_t size, bytes[2];	//size can be of one or two bytes
	bool make = false;      //make or break code
	int r , ipc_status;
	message msg;
	bool continuar = false;  //flag for interruption

	if (kbc_subscribe_int(&keyboardirq) == 1) { 		// Check if subscription worked
		printf("Could not subscribe Keyboard \n");
		return 1;
	}
	while (scancode != ESC_BREAKCODE) {			// function should exit when the user releases the Esc key
		/*Get a request message.*/
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("ERROR: driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { 									// received notification
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: 																	// hardware interrupt notification
				if (msg.m_notify.interrupts & keyboardirq ) { // subscribed interrupt
					if (assembly) {
						kbc_asm_ih();

					} else {
						kbc_ih();   //keyboard handler
					}
					if (continuar)
					{
						bytes[1] = scancode; 				// Add second byte to the array
						continuar = false;
					}
					else if (scancode == TWO_BYTE_SCANCODE) { 	// 3 - Scancode is 2-byte
						size = 2;
						bytes[0] = scancode; 	
						continuar = true;						// Add first byte to the array
						//can only remove one code for the buffer so 2 byte will be removed in another call
					} 
					else {												// 3 - Scancode is 1-byte
						size = 1;															
						bytes[0] = scancode;				// Add scancode to the array
						continuar = false;					//already remove everything from the buffer to print the code
					}
					if (!continuar){
						if (scancode & MAKE_CODE){	// 4 - Checks if code is make or break
							make = false;	//break code
						}
						else {
							make = true;  //make code
						}
						kbd_print_scancode(make, size, bytes); //prints the code
					}
				}
				break;
			default:
				break;	// no other notifications expected: do nothing
			}
		}
		else { 			// received a standard message, not a notification
			// no standard messages expected: do nothing
		}
	}

  if (kbc_unsubscribe_int() == 1) { // Check if subscription worked
		printf("Could not unsubscribe Keyboard \n");
		return 1;
	}
	if (!assembly) {
		kbd_print_no_sysinb(cnt);  //prints the counter of sys inb
		cnt = 0; //Reset the counter of sys inb
	}
	return 0;
}

int (kbd_test_poll)() {
	uint8_t size, bytes[2];	//size can be of one or two bytes
	uint8_t status;
	bool make = false;
	scancode = 0;
	
	//LCF Disables the interrupts automaticly

	//Exits upon release of the ESC key
	while(scancode != ESC_BREAKCODE)	{				// Polling only stops when the user releases ESC
		sys_inb_cnt(STAT_REG, &status);					// 1 - Checks the status register
		// 2 - Checks if OBF BIT is 1 and AUX is 0, and if there is no parity or timeout error
		if ((status & STAT_REG_OBF) && !(status & STAT_REG_AUX) && !(status & STAT_REG_PAR || status & STAT_REG_TIMEOUT)) {
			sys_inb_cnt(OUT_BUF, &scancode);
			if (scancode == TWO_BYTE_SCANCODE) {	// 3 - Scancode is 2-byte
				size = 2;
				bytes[0] = scancode; 								// Add first byte to the array
				sys_inb_cnt(OUT_BUF, &scancode);		// Read second byte
				bytes[1] = scancode; 								// Add second byte to the array
				if (scancode & MAKE_CODE)						// 4 - Checks if code is make or break
					make = false;
				else
					make = true;
				kbd_print_scancode(make, size, bytes);
			}
			else {																// 3 - Scancode is 1-byte
				size = 1;															
				bytes[0] = scancode;								// Add scancode to the array
				if (scancode & MAKE_CODE)						// 4 - Checks if code is make or break
					make = false;
				else
					make = true;

				kbd_print_scancode(make, size, bytes);
			
			}
						
		}
		else { 																		// If OBF is not full wait for it
			tickdelay(micros_to_ticks(DELAY_US));		// 5 - Makes keyboard respond to a command in 20 ms
		}
	}

	kbd_print_no_sysinb(cnt);

	//Re-enable the interrupts
	if(enable_interrupts())	{
		printf("Could not enable the interrupts\n");
		return 1;
	}

	cnt = 0; //Reset the counter

	return 0;
}
int(kbd_test_timed_scan)(uint8_t n){
	uint8_t size, bytes[2];	//size can be of one or two bytes
	bool make = false;
	int r;
	int ipc_status;
	message msg;
	bool continuar = false;
	uint8_t timerirq;

	if (kbc_subscribe_int(&keyboardirq) == 1) { 		// Check if kbd subscription worked
		printf("Could not subscribe Keyboard \n");
		return 1;
	}
	if (timer_subscribe_int(&timerirq) == 1) { 			// Check if timer subscription worked
		printf("Could not subscribe timer irq!\n");
		return 1;
	}

	while (scancode != ESC_BREAKCODE && (counter / 60.0 < n)) {			// function should exit when the user releases the Esc key
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("ERROR: driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { 									// received notification
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: 																	// hardware interrupt notification
				if (msg.m_notify.interrupts & keyboardirq ) { // subscribed interrupt
					
					kbc_ih();   //keyboard interrupt handler
					if (continuar)
					{
						bytes[1] = scancode; 					// Add second byte to the array
						continuar = false;
					}
					else if (scancode == TWO_BYTE_SCANCODE) { 	// 3 - Scancode is 2-byte
						size = 2;
						bytes[0] = scancode; 	
						continuar = true;							// Add first byte to the array
					} 
					else {													// 3 - Scancode is 1-byte
						size = 1;															
						bytes[0] = scancode;					// Add scancode to the array
						continuar = false;
					}

					if (!continuar){
						if (scancode & MAKE_CODE)			// 4 - Checks if code is make or break
							make = false;
						else
							make = true;
						kbd_print_scancode(make, size, bytes); //prints the code
						counter = 0; //reset the counter
					}
				}
				else if (msg.m_notify.interrupts &timerirq) { // subscribed interrupt
					// dealing with the interruption call
					timer_int_handler(); // if interruption increment timer
				}
			
				break;
			default:
				break;	// no other notifications expected: do nothing
			}
		}
		else { 			// received a standard message, not a notification
			// no standard messages expected: do nothing
		}
	}

 	if (kbc_unsubscribe_int() == 1) { // Check if kbd unsubscription worked
		printf("Could not unsubscribe Keyboard \n");
		return 1;
	}
	if (timer_unsubscribe_int() == 1) { // Check if timer unsubscription worked
		printf("Could not unsubscribe timer irq!\n");
		return 1;
	}

	kbd_print_no_sysinb(cnt);
	cnt = 0; //Reset the counter of sysinb

	return 0;
}
