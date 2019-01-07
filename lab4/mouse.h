#ifndef _MOUSE_H_
#define _MOUSE_H_

#include <minix/syslib.h>
#include <minix/sysutil.h>

/**
 * @brief Subscribes and enables Mouse interrupts
 *
 * @param bit_no Address of memory to be initialized with the mouse
 *               peripheral interface controller bit number to be set
 *               in the mask returned upon an interrupt
 * 
 * @return Return 0 upon success and non-zero otherwise
 */

int mouse_subscribe_int(uint16_t *bit__no);

/**
 * @brief Unsubscribes and disables Mouse interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */

int mouse_unsubscribe_int();

/** 
 * @brief Reads the content of the Output Buffer
 * 
 * Checks if there is any timeout or parity error and if the
 * information is coming from the mouse
 * 
 * Polls the Status Register until the Output Buffer is full
 * 
 * @param content Adddress of memory where the content read from the
 *                Output Buffer will be written to
 * 
 * @return Return 0 upon success and non-zero otherwise
 */

int kbc_read_out_buf(uint8_t *content);

/** 
 * @brief Writes command to specified port of the KBC
 * 
 * Polls the Status Register until the Input Buffer is empty
 * 
 * @param port Address of the port the command is being written to
 * @param cmd Command that will be written to the KBC
 * 
 * @return Return 0 upon success and non-zero otherwise
 */

int kbc_write(port_t port, uint8_t cmd);

/** 
 * @brief Writes byte to mouse
 * 
 * Sends write byte to mouse command to the control register
 * 
 * Sends mouse command to the Input Buffer
 * 
 * Receives acknowledgement and checks if the acknowledgement is correct
 * 
 * If not correct, tries again one more time
 * 
 * @param cmd Command that will be written to the mouse
 * 
 * @return Return 0 upon success and non-zero otherwise
 */

int kbc_write_mouse_command(uint8_t cmd);

/** 
 * @brief Receives an incomplete packet and parses it
 * 
 * Packet contains only the 3 byte array
 * 
 * Checks the bits of the first byte and completes the packet data
 * 
 * @param pp Memory address containing the incomplete packet
 * 
 * @return Return 0 upon success and non-zero otherwise
 */

int mouse_parse_packet(struct packet *pp);

/** 
 * @brief 
 *  the function detects if the user draws 
 * an inverted V, from left to right
 * The first line must be drawn while the left button, and no other,
 * is pressed down, and the second line must be drawn while the right 
 * button, and no other, is pressed down
 * 
 * @param 
 * pp Memory address containing a packet
 * x_len is the length on variable x, the one that
 * makes the length of the line valid or invalid
 * tolerance is the intervale that is accepted by the machine
 *     
 * @return Return 0 upon success and non-zero otherwise
 */

void gest_handler(struct packet *pp, uint8_t x_len, uint8_t tolerance);

/** 
 * @brief 
 * this function detects the events that ocurrer and are important
 * for the state machine
 * 
 * @param 
 * pp Memory address containing a complte packet
 *     
 * @return Return 0 upon success and non-zero otherwise
 */

struct mouse_ev *mouse_event_detect(struct packet *pp);

enum state_t {
    INIT,       /* First state, wainting to press the left bottom  */
    DRAW,       /* 2 state, drawing the first line */
    DONELINE,   /* 3 state, wainting to press the right bottom */
    DRAW1,      /* 4 state , drawing the second line*/
} ;

#endif
