// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you
#include "mouse.h"
#include "i8254.h"
#include "i8042.h"

int main(int argc, char *argv[])
{
	// sets the language of LCF messages (can be either EN-US or PT-PT)
	lcf_set_language("EN-US");

	// enables to log function invocations that are being "wrapped" by LCF
	// [comment this out if you don't want/need/ it]
	lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

	// enables to save the output of printf function calls on a file
	// [comment this out if you don't want/need it]
	lcf_log_output("/home/lcom/labs/lab4/output.txt");

	// handles control over to LCF
	// [LCF handles command line arguments and invokes the right function]
	if (lcf_start(argc, argv))
		return 1;

	// LCF clean up tasks
	// [must be the last statement before return]
	lcf_cleanup();

	return 0;
}

extern int mouse_id;
extern uint8_t oneByte; // byte read from the output

int(mouse_test_packet)(uint32_t cnt)
{
	unsigned int byteNumber = 0; // counts the number of bytes read
	struct packet p;			 // packet with 3 bytes
	uint32_t printsCnt = 0;		 // number of packets printed
	uint16_t mouseirq;
	int r, ipc_status;
	message msg;

	//... Subscribing Mouse Interrupts
	if (mouse_subscribe_int(&mouseirq))
	{ // Check if subscription worked
		printf("Could not subscribe Mouse!\n");
		return 1;
	}
	
	/* LCF enables stream Mode */
	
	//... Enabling Data Reporting
	sys_irqdisable(&mouse_id); // disable notifications
	if (kbc_write_mouse_command(MOUSE_ENA))
	{ // send disable data report command
		printf("Could not disable data reporting!");
		return 1;
	}
	sys_irqenable(&mouse_id); // enable notifications

	while (cnt > printsCnt)
	{ /* ends when it has printed the number in ctn */
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
				if (msg.m_notify.interrupts & mouseirq)
				{				// subscribed interrupt
					mouse_ih(); //must read only one byte
					if ((byteNumber == 0 && (BIT(3) & oneByte)) || byteNumber == 1 || byteNumber == 2)
					{								   //access the struct bytes
						p.bytes[byteNumber] = oneByte; // bytes 0, 1 or 2
						byteNumber++;				   // increments the counter to know in the next interrupt
					}
					if (byteNumber == 3)
					{							// 3 bytes haven been read and there's no error
						byteNumber = 0;			// reset to start counting new packets
						mouse_parse_packet(&p); // parses packet
						mouse_print_packet(&p); // prints packet
						printsCnt++;			//counts the prints for the end of the loop
					}
				}
				break;
			default:
				break; // no other notifications expected: do nothing
			}
		}
		else
		{   // received a standard message, not a notification
			// no standard messages expected: do nothing
		}
	}

	//... Disabling Data Reporting
	sys_irqdisable(&mouse_id); // disable notifications
	if (kbc_write_mouse_command(MOUSE_DIS))
	{ // send disable data report command
		printf("Could not disable data reporting!");
		return 1;
	}
	sys_irqenable(&mouse_id); // enable notifications

	//... Unsubscribing mouse interrupts
	if (mouse_unsubscribe_int())
	{
		printf("Could not unsubscribe Mouse \n");
		return 1;
	}

	return 0;
}

int(mouse_test_remote)(uint16_t period, uint8_t cnt)
{
	struct packet p;	   // packet with 3 bytes
	uint8_t printsCnt = 0; // number of packets printed
	uint8_t byte;		   // byte read from the OUTPUT_BUFFER
	uint8_t byteCnt = 0;

	/*
	****LCF does this automatically****

	//... Disabling MINIX's mouse IH
	//... Enables Remote Mode
  	//... Enabling Data Reporting
  	*/

	//... Displaying mouse packets
	while (cnt > printsCnt)
	{
		//... Sending read mouse data command
		if (byteCnt == 0)
		{ // Only send command if it is the first of 3 bytes
			if (kbc_write_mouse_command(MOUSE_READ))
			{
				printf("Could not send 'Read Data' command!\n");
				return 1;
			}
		}

		//... Reading a byte
		if (kbc_read_out_buf(&byte))
		{
			tickdelay(micros_to_ticks(DELAY_US)); // if not valid wait and continue
			continue;
		}

		//... Checking byte order
		p.bytes[byteCnt] = byte;
		switch (byteCnt)
		{
		case 0:
			if (byte & BIT(3))
				byteCnt++; // Increments byte counter
			break;
		case 1:
			byteCnt++; // Increments byte counter
			break;
		case 2:
			mouse_parse_packet(&p);					   // Parses the packet
			mouse_print_packet(&p);					   // Prints the packet
			printsCnt++;							   // Increments print counter
			byteCnt = 0;							   // Resets byte counter
			tickdelay(micros_to_ticks(period * 1000)); // Waits for the set period of time (in microseconds)
			break;
		}
	}

	//... Enabling Stream Mode
	if (kbc_write_mouse_command(MOUSE_STREAM))
	{
		printf("Could not enable stream mode!");
		return 1;
	}

	//... Disables Data Reporting
	if (kbc_write_mouse_command(MOUSE_DIS))
	{
		printf("Could not disable data reporting!");
		return 1;
	}

	//... Reseting the KBC command byte to Minix's default value
	if (kbc_write(CTRL_REG, KBC_WRITE_CMD))
	{ // Sends Write Command
		printf("Could not reset KBC command byte to default!");
		return 1;
	}
	if (kbc_write(IN_BUF, minix_get_dflt_kbc_cmd_byte()))
	{ // Writes Command Byte
		printf("Could not reset KBC command byte to default!");
		return 1;
	}

	return 0;
}

int(mouse_test_async)(uint8_t idle_time)
{
	unsigned int byteNumber = 0; // counts the number of bytes read
	struct packet p;			 // packet with 3 bytes
	uint16_t mouseirq;
	uint8_t timerirq;
	uint32_t freq = sys_hz();
	int r, ipc_status;
	message msg;
	extern unsigned int counter; // timer's counter

	//... Subscribing timer interrupts
	if (timer_subscribe_int(&timerirq))
	{
		printf("Could not subscribe timer irq!\n");
		return 1;
	}
	//... Subscribing mouse interrupts
	if (mouse_subscribe_int(&mouseirq))
	{
		printf("Could not subscribe Mouse \n");
		return 1;
	}

	//... Enabling Data Reporting
	sys_irqdisable(&mouse_id); // disable notifications
	if (kbc_write_mouse_command(MOUSE_ENA))
	{ // send disable data report command
		printf("Could not disable data reporting!");
		return 1;
	}
	sys_irqenable(&mouse_id); // enable notifications

	while (counter < (idle_time * freq))
	{ /* ends after idle_time passed */
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
				if (msg.m_notify.interrupts & mouseirq)
				{				 // mouse interrupt
					counter = 0; // resets the timer counter to 0
					mouse_ih();  // must read only one byte
					if ((byteNumber == 0 && (BIT(3) & oneByte)) || byteNumber == 1 || byteNumber == 2)
					{								   //access the struct bytes
						p.bytes[byteNumber] = oneByte; // bytes 0, 1 or 2
						byteNumber++;				   // increments the counter to know in the next interrupt
					}
					if (byteNumber == 3)
					{							// 3 bytes haven been read and there's no error
						byteNumber = 0;			// reset to start counting new packets
						mouse_parse_packet(&p); // parses packet
						mouse_print_packet(&p); // prints packet
					}
				}
				else if (msg.m_notify.interrupts & timerirq)
				{						 // timer interrupt
					timer_int_handler(); // if interruption increment timer
				}
				break;
			default:
				break; // no other notifications expected: do nothing
			}
		}
		else
		{   // received a standard message, not a notification
			// no standard messages expected: do nothing
		}
	}

	//... Disabling Data Reporting
	sys_irqdisable(&mouse_id); // disable notifications
	if (kbc_write_mouse_command(MOUSE_DIS))
	{ // send disable data report command
		printf("Could not disable data reporting!");
		return 1;
	}
	sys_irqenable(&mouse_id); // enable notifications

	//... Unsubscribing mouse interrupts
	if (mouse_unsubscribe_int())
	{
		printf("Could not unsubscribe Mouse \n");
		return 1;
	}
	//... Unsubscribing timer interrupts
	if (timer_unsubscribe_int())
	{
		printf("Could not unsubscribe timer irq!\n");
		return 1;
	}
	return 0;
}


int(mouse_test_gesture)(uint8_t x_len, uint8_t tolerance)
{
	bool end = false;
	struct packet p;			 // packet with 3 bytes
	unsigned int byteNumber = 0; // counts the number of bytes read
	uint16_t mouseirq;
	int r, ipc_status;
	message msg;

	//... Subscribing mouse interrupts
	if (mouse_subscribe_int(&mouseirq) == 1)
	{ // Check if subscription worked
		printf("Could not subscribe Mouse \n");
		return 1;
	}

	// DAR DISABLE AS NOTIFICATIONS - PMMS
	sys_irqdisable(&mouse_id);

	//... Enabling Data Reporting
	if (kbc_write_mouse_command(MOUSE_ENA))
	{
		printf("Could not enable data reporting!\n");
		return 1;
	}

	// DAR ENABLE AS NOTIFICATIONS - PMMS
	sys_irqenable(&mouse_id);

	while (!end)
	{
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
				if (msg.m_notify.interrupts & mouseirq)
				{
					mouse_ih(); // must read only one byte
					if ((byteNumber == 0 && (BIT(3) & oneByte)) || byteNumber == 1 || byteNumber == 2)
					{								   //access the struct bytes
						p.bytes[byteNumber] = oneByte; // bytes 0, 1 or 2
						byteNumber++;				   // increments the counter to know in the next interrupt
					}
					if (byteNumber == 3)
					{					// 3 bytes haven been read and there's no error
						byteNumber = 0; // reset to start counting new packets
						gest_handler(&p, x_len, tolerance);
						mouse_print_packet(&p); // prints packet
					}
				}
				break;
			default:
				break; // no other notifications expected: do nothing
			}
		}
	}
	//... Disabling Data Reporting
	sys_irqdisable(&mouse_id); // disable notifications
	if (kbc_write_mouse_command(MOUSE_DIS))
	{ // send disable data report command
		printf("Could not disable data reporting!");
		return 1;
	}
	sys_irqenable(&mouse_id); // enable notifications

	//... Unsubscribing mouse interrupts
	if (mouse_unsubscribe_int())
	{
		printf("Could not unsubscribe Mouse \n");
		return 1;
	}

	return 0;
}
