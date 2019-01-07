#ifndef _LCOM_MACROS_H_
#define _LCOM_MACROS_H_

#define BIT(n)          (0x01<<(n))

#define LIN_FRAME_BUF_BIT   BIT(14) /* Linear frame buffer bit */
#define FREQ                60 //Default Minix frequency

/************************/
/*** Interrupt Vector ***/
/************************/

#define VIDEO_CARD_INT_NO     0x10  /* Video Card Interrupt Number */
#define PC_CONFIG_INT_NO      0x11  /* PC Config Interrupt Number */
#define MEMORY_CONFIG_INT_NO  0x12  /* Memory Config Interrupt Number */
#define KEYBOARD_INT_NO       0x16  /* Keyboard Interrupt Number */

/***********************/
/**** AH Functions *****/
/***********************/

#define VBE_FUNCTION    0x4F  /* VBE Function */
#define SET_VIDEO_MODE  0x00  /* Set Video Mode Function */

/************************/
/***** AL Functions *****/
/************************/

#define VBE_CONTROL_INFO  0x00  /* Return VBE Controller Information */
#define VBE_MODE_INFO     0x01  /* Return VBE Mode Information */
#define VBE_MODE_SET      0x02  /* Set VBE Mode */
#define TEXT_MODE_SET     0x03  /* Set Text Mode, 25 Lines X 80 Columns, 16 colors */

/************************/
/**** Graphic Modes *****/
/************************/

#define VBE_GRAPHIC_1   0x105 /* 1024x768  Indexed Colors  8 bits/pixel */
#define VBE_GRAPHIC_2   0x110 /* 640x480   Direct Colors   15 bits ((1:)5:5:5) */
#define VBE_GRAPHIC_3   0x115 /* 800x600   Direct Colors   24 bits (8:8:8) */
#define VBE_GRAPHIC_4   0x11A /* 1280x1024 Direct Colors   16 bits (5:6:5) */
#define VBE_GRAPHIC_5   0x11A /* 1152x864  Direct Colors   32 bits ((8:)8:8:8) */

/************************/
/*** AH Return Values ***/
/************************/

#define VBE_RET_SUC     0x00 /* Function call succeeded */
#define VBE_RET_FAIL    0x01 /* Function call failed */
#define VBE_RET_UNSUP   0x02 /* Function not supported in HW config */
#define VBE_RET_INV     0x03 /* Function invalid in current video mode */

#endif
