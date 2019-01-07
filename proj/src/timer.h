#ifndef _TIMER_H
#define _TIMER_H

#include <stdbool.h>
#include <stdint.h>

/** @defgroup timer timer
 * @{
 *
 * Functions for using the i8254 timers.
 * It only subscribes and unsubscribes the timer.
 * The counter is in the struct minix force, as time alive.
 */


/**
 * @brief Subscribes and enables Timer 0 interrupts
 *
 * @param bit_no address of memory to be initialized with the
 *         bit number to be set in the mask returned upon an interrupt
 * @return Return 0 upon success and non-zero otherwise
 */
int(timer_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes Timer 0 interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int(timer_unsubscribe_int)();



#endif /* _TIMER_H */
