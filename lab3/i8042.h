#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#define BIT(n) (0x01<<(n))

#define DELAY_US        20000   /* IBM's specification of the i8042 requires the keyboard to respond to a command in 20 ms */
#define KBD_IRQ_ADDRESS 0x09 /* KBD's address in the PIC vector */

/***********************/
/*** Status Register ***/
/***********************/

#define STAT_REG_PAR		  BIT(7)  /* Parity Error       - invalid data */
#define STAT_REG_TIMEOUT	BIT(6)  /* Timeout Error      - invalid data */
#define STAT_REG_AUX		  BIT(5)  /* Mouse Data */
#define STAT_REG_INH		  BIT(4)  /* Inhibit Flag       - if keyboard is inhibited */
#define STAT_REG_A2       BIT(3)  /* A2 Input Line      - 0 if data byte - 1 if command byte */
#define STAT_REG_SYS		  BIT(2)  /* System Flag        - 0 if system in power-on reset - 1 if system already initialized */ 
#define STAT_REG_IBF	   	BIT(1)  /* Input Buffer Full  - do not write commands or arguments */
#define STAT_REG_OBF		  BIT(0)  /* Output Buffer Full - data available for reading */

/***********************/
/**** KBC Commands *****/
/***********************/

#define KBC_READ_CMD		0x20    /* Returns Command Byte */
#define KBC_WRITE_CMD   0x60    /* Writes Command Byte */
#define KBC_CHECK_CMD   0xAA    /* Checks KBC (self-test), returns: 0x55 if ok, 0xfc if error */
#define KBC_INT_CMD		  0xAB    /* Checks KBD Interface, returns: 0 if ok */
#define KBC_DIS_CMD     0xAD    /* Disables KBD Interface */
#define KBC_ENA_CMD		  0xAE    /* Enables KBD Interface */

/************************/
/*** KBC Command Byte ***/
/************************/

#define KBC_CMD_BYTE_DIS2		BIT(5)    /* Disables Mouse */
#define KBC_CMD_BYTE_DIS		BIT(4)    /* Disables Keyboard Interface */
#define KBC_CMD_BYTE_INT2		BIT(1)    /* Enables Interrupt on OBF, from mouse */
#define KBC_CMD_BYTE_INT		BIT(0)    /* Enables Interrupt on OBF, from keyboard */

/************************/
/******* KBC Ports ******/
/************************/

#define OUT_BUF         0x60    /* Output Buffer */
#define IN_BUF          0x60    /* Input Buffer */
#define STAT_REG        0x64    /* Status Register */
#define KBC_CMD_REG     0x64    /* Command Register */
#define KBC_CMD_ARG     0x60    /* Command Arguments Adress */

/************************/
/******* Scancodes ******/
/************************/

#define ESC_BREAKCODE       0x81
#define TWO_BYTE_SCANCODE   0xE0      /* Two-byte long scancodes usually use 0xE0 as their first byte */
#define MAKE_CODE            BIT(7)
#endif
