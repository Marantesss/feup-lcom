#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <minix/syslib.h>
#include <minix/sysutil.h>
#include "i8042.h"

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
 * @brief Mask function of sys_inb(port_t port, uint32_t *byte)
 * 
 * Counts the number of sys_inb() calls
 * Avoids the need to convert uint32_t to uint8_t when calling sys_inb()
 * 
 * @param port Port's code where the byte is
 * @param *byte Will contain port's Output
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int sys_inb_cnt(port_t port, uint8_t *byte);

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
int kbc_read_out_buf(uint8_t *content);

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
int kbc_write_command(uint8_t cmd);

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
int kbc_write_argument(uint8_t arg);

/** 
 * @brief Handles keyboard interrupts
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
void (kbc_ih)(void);

#endif
