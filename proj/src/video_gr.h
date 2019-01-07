#ifndef _VIDEO_GR_H
#define _VIDEO_GR_H

#include <lcom/lcf.h>
#include <math.h>
#include "videomacros.h"
#include "vbe.h"

/** @defgroup video_gr video_gr
 * @{
 *
 * Basic functions to work with MINIX in graphics mode
 */

/**
 * @brief Function to get the horizontal resolution in video mode
 * 
 * @param horizontal resolution
 */
unsigned get_hres();

/**
 * @brief Function to get the vertical resolution in video mode
 * 
 * @param vertical resolution
 */
unsigned get_vres();

/**
 * @brief Function to get the number of bits per pixel in video mode
 * 
 * @param bits per pixel
 */
unsigned get_bits_per_pixel();

/**
 * @brief Function to get the number of bytes per pixel in video mode
 * 
 * @param bytes per pixel
 */
unsigned get_bytes_per_pixel();

/**
 * @brief Function to get the temporary video memory for double buffering
 * 
 * @param temporary video memory
 */
char *get_tmp_video_mem();

/**
 * @brief Function to get the actual video memory
 * 
 * @param actual video memory
 */
char *get_video_mem();

/**
 * @brief Function to initialize video mode with the mode passed as argument
 */
void *(vg_init)(uint16_t mode);

/**
 * @brief Overwrites temporary video memory to actual video memory
 */
void flip_double_buffer();

/**@}*/

#endif /* _VIDEO_GR_H */
