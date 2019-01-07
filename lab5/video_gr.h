#pragma once

#include <stdint.h>

void *(vg_init)(uint16_t mode);

unsigned get_hres();

unsigned get_vres();

unsigned get_bits_per_pixel();

unsigned get_bytes_per_pixel();

char * get_video_mem();

void clear_video_mem();

void  draw_xpm_line(char *xpm_mem, uint16_t x, uint16_t y, uint16_t width);

void draw_xpm(char *xpm_mem, uint16_t width, uint16_t height, uint16_t x, uint16_t y);

int vg_pixel(uint16_t x, uint16_t y, uint32_t color);

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

uint32_t next_color(uint8_t no_rectangles, uint8_t col,  uint8_t row, uint32_t first, uint8_t step);

int vbe_get_info(vg_vbe_contr_info_t *vmi_p);

int (vg_exit)(void);

