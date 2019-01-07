#pragma once

#include <stdint.h>

/** 
 * @brief 
 * 
 *
 * 
 * @param 
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (video_test_init)(uint16_t mode, uint8_t delay);
/** 
 * @brief 
 * 
 *
 * 
 * @param 
 * mode	- VBE graphics mode to use
 * x	- horizontal coordinate of the top left corner
 * y	- vertical coordinate of the top left corner
 * width	- length in pixels of the rectangle along the horizontal direction
 * height	- length in pixels of the rectangle along the vertical direction
 * color - color to set the pixel 
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
/** 
 * @brief 
 * 
 *
 * 
 * @param 
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step);

int (video_test_xpm)(const char *xpm[], uint16_t x, uint16_t y);

int (video_test_move)(const char *xpm[], uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf, int16_t speed, uint8_t fr_rate);

int (video_test_controller)();