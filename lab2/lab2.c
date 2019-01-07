#include <lcom/lcf.h>

#include <lcom/lab2.h>
#include <lcom/timer.h>

#include <stdbool.h>
#include <stdint.h>

extern unsigned int counter;
// Extern allows to access "counter" varaible in timer.c


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
	uint8_t conf;
	if (timer > 2 || timer < 0) { // timer can only be between 0 and 2
		printf("Invalid timer!\n");
		return 1;
	}

	if (timer_get_conf(timer, &conf) == 1) { // Op failed
		printf("Could not get configuration!\n");
		return 1;
	}
	if (timer_display_conf(timer, conf, field) == 1) { // Op failed
		printf("Could not display configuration!\n");
		return 1;
	}
	return 0;
}

int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
	if (timer_set_frequency(timer, freq) == 1) { // Op failed
		printf("Could not set configuration!\n");
		return 1;
	}
	else
		return 0;
}

int(timer_test_int)(uint8_t time) {
	int r;
	int ipc_status;
	uint8_t timerirq;
	message msg;

	if (timer_subscribe_int(&timerirq) == 1) { // Check if subscription worked
		printf("Could not subscribe timer irq!\n");
		return 1;
	}

	while (counter / 60.0 < time) { // Loop until counter reaches the time given as the argument
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d!", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { // received notification
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: // hardware interrupt notification
				if (msg.m_notify.interrupts &timerirq) { // subscribed interrupt
														 // dealing with the interruption call
					timer_int_handler(); // if interruption increment timer
					if ((counter % 60) == 0) // each second
						timer_print_elapsed_time();  //print one message per second
				}
				break;

			default:
				break; // no other notifications expected: do nothing
			}

		}
		else { // received a standard message, not a notification
			   // no standard messages expected: do nothing
		}
	}
	if (timer_unsubscribe_int() == 1) { //op failed
		printf("Could not unsubscribe timer irq!\n");
		return 1;
	}
	return 0;
}


int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  *lsb = (uint8_t)val ; // Get the LSBs from val
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  val >>=8; // Shift right 8 bits (Mode the MSB to the LSB position)
  *msb = (uint8_t)val; // Get the MSB (LSB because of the shift) from val
  return 0;
}
