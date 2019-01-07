#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <lcom/lcf.h>
#include "i8254.h"
#include "i8042.h"

/** @defgroup keyboard keyboard
 * @{
 *
 * Functions to interact with the i8042 KBC
 */

/** 
 * @brief Subscribes keyboard interrupts
 * 
 * @param *bit__no contains address of kbd interrupt bit set to 1
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int kbc_subscribe_int(uint8_t *bit__no);

/** 
 * @brief Unsubscribes keyboard interrupts
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int kbc_unsubscribe_int();

/** 
 * @brief Disables Minix interrupts
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int disable_interrupts();

/** 
 * @brief Enables Minix interrupts
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int enable_interrupts();

/** 
 * @brief Reads Keyboard Controller's Output Buffer
 * 
 * Checks Output Buffer's status
 * Checks for parity or timeout errors
 * 
 * @param *content Will contain Output Buffer's Byte
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int kbc_read_out_buf(uint32_t *content);

/** 
 * @brief Writes command to the Keyboard Controller
 * 
 * Checks Input Buffer's status
 * Checks for parity or timeout errors
 * 
 * @param cmd contains command code
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int kbc_write_command(uint32_t cmd);

/** 
 * @brief Writes argument to the Keyboard Controller
 * 
 * Checks Input Buffer's status
 * Checks for parity or timeout errors
 * 
 * @param arg contains argument
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int kbc_write_argument(uint32_t arg);

/** 
 * @brief Handles keyboard interrupts
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
void (kbc_ih)(void);

/** 
 * @return scancode that came from the buffer
 */
uint8_t getScancode();

/**@}*/

#endif /* _KEYBOARD_H_ */
