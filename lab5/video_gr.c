#include <lcom/lcf.h>
#include "macros.h"
#include "video_gr.h"
#include <math.h>
#include "vbe.h"

static char *video_mem;          /* Process (virtual) address to which VRAM is mapped */
static unsigned h_res;           /* Horizontal resolution in pixels */
static unsigned v_res;           /* Vertical resolution in pixels */
static unsigned bits_per_pixel;  /* Number of VRAM bits per pixel */
static unsigned bytes_per_pixel; /* Number of VRAM bytes per pixel */
vbe_mode_info_t vmi_p;

void *(vg_init)(uint16_t mode)
{

  if (vbe_get_info_mode(mode, &vmi_p) != 0)
  { // if Operation fail
    printf("vg_init(): failed to get mode \n");
    return NULL;
  }

  struct reg86u reg86;
  int r;
  struct minix_mem_range mr;
  static unsigned int vram_base; /* VRAM's physical addresss */
  static unsigned int vram_size; /* VRAM's size, we can also use the frame-buffer size, instead */

  // Initializing global variables with screen resolution and color depth
  h_res = vmi_p.XResolution;
  v_res = vmi_p.YResolution;
  bits_per_pixel = vmi_p.BitsPerPixel;

  bytes_per_pixel = ceil(bits_per_pixel / 8);

  vram_base = vmi_p.PhysBasePtr;
  vram_size = h_res * v_res * bytes_per_pixel;

  // Allow memory mapping
  mr.mr_base = (phys_bytes)vram_base;
  mr.mr_limit = mr.mr_base + vram_size;

  // granting the process the permission to map the address range
  if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
  {
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);
    return NULL;
  }
  // Map memory
  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

  if (video_mem == MAP_FAILED)
  {
    panic("couldn't map video memory");
    return NULL;
  }

  memset(&reg86, 0, sizeof(reg86));        /* zero the structure */
  reg86.u.b.intno = VIDEO_CARD_INT_NO;     /* BIOS video services */
  reg86.u.b.ah = VBE_FUNCTION;             /* invoking VBE function */
  reg86.u.b.al = VBE_MODE_SET;             /* Set VBE Mode */
  reg86.u.w.bx = LIN_FRAME_BUF_BIT | mode; /* Set specific graphic mode */

  //temporarily switches from 32-bit protected mode to 16-bit real-mode to access the BIOS calls
  if (sys_int86(&reg86) != OK)
  { // if Operation fail
    printf("vg_init(): sys_int86() failed \n");
    return NULL;
  }

  // check ax
  if (reg86.u.w.ax != 0x004F)
    return NULL;

  return (void *)video_mem;
}

unsigned get_hres()
{
  return h_res;
}

unsigned get_vres()
{
  return v_res;
}

unsigned get_bits_per_pixel()
{
  return bits_per_pixel;
}

char *get_video_mem()
{
  return video_mem;
}

void clear_video_mem()
{
  uint8_t clear = 0;
  for (unsigned int i = 0; i < h_res * v_res; i++)
  {
    *(video_mem + i) = clear;
  }
}

void draw_xpm_line(char *xpm_mem, uint16_t x, uint16_t y, uint16_t width)
{
  char *line = (char *)(video_mem + (x + y * h_res) * bytes_per_pixel);

  for (uint16_t i = 0; i < width; ++i)
  {
    *line++ = *xpm_mem++;
  }
}

void draw_xpm(char *xpm_mem, uint16_t width, uint16_t height, uint16_t x, uint16_t y)
{
  for (uint16_t i = 0; i < height; ++i)
  {
    draw_xpm_line(xpm_mem, x, y + i, width);
    xpm_mem += width;
  }
}

int vg_pixel(uint16_t x, uint16_t y, uint32_t color)
{
  if (x >= h_res || y >= v_res)
    return 1;

  for (unsigned int j = 0; j < bytes_per_pixel; j++)
  {
    //col is the register with the necessary bits in RGB order
    uint8_t col = (color >> bits_per_pixel * j);
    //Putting only necessary bytes into the memory
    *(video_mem + (y * h_res + x) * bytes_per_pixel + j) = col;
  }
  return 0;
}

int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color)
{
  for (int i = 0; i < len; i++)
  {
    if (vg_pixel(x + i, y, color) == 1)
      return 1;
  }
  return 0;
}

int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color)
{
  //width and heigth in number of pixels
  for (int i = 0; i < height; i++)
  {
    if (vg_draw_hline(x, y + i, width, color) == 1)
      return 1;
  }
  return 0;
}

uint32_t next_color(uint8_t no_rectangles, uint8_t col, uint8_t row, uint32_t first, uint8_t step)
{

uint32_t aux = first;

if (bits_per_pixel == 8)
{
  aux = (first + (row * no_rectangles + col) * step) % (1 << bits_per_pixel);
}
else
{
  uint32_t red, blue, green, others;
  
  others = 32 - (vmi_p.GreenMaskSize + vmi_p.RedMaskSize + vmi_p.BlueMaskSize);

  red = (aux << (32 - (vmi_p.GreenMaskSize + vmi_p.RedMaskSize + vmi_p.BlueMaskSize)));
  red = (red >> (vmi_p.GreenMaskSize + vmi_p.BlueMaskSize));

  green = (first << (others + vmi_p.RedMaskSize));
  green = (green >> (others + vmi_p.RedMaskSize + vmi_p.BlueMaskSize));

  blue = first << (others + vmi_p.RedMaskSize + vmi_p.GreenMaskSize);
  blue = (blue >> (others + vmi_p.RedMaskSize + vmi_p.GreenMaskSize));

  uint32_t aux1 = 0, aux2 = 0, aux3 = 0;

  aux1 = (red + col * step) % (1 << vmi_p.RedMaskSize);
  aux1 = aux1 << (vmi_p.RedFieldPosition);

  aux2 = (green + row * step) % (1 << vmi_p.GreenMaskSize);
  aux2 = aux2 << (vmi_p.GreenFieldPosition);

  aux3 = (blue + (col + row) * step) % (1 << vmi_p.BlueMaskSize);
  aux3 = aux3 << (vmi_p.BlueFieldPosition);

  aux = aux1 | aux2 | aux3;

}

return aux;
}

int vbe_get_info(vg_vbe_contr_info_t *vmi_p) {
  
  mmap_t temp_mem;
  struct reg86u reg86;

	lm_init(true);
 	lm_alloc(256, &temp_mem);
  
  memset(&reg86, 0, sizeof(reg86));	/* zero the structure */

  reg86.u.w.ax = 0x4F00; /* VBE get mode info */
	/* translate the buffer linear address to a far pointer */
	reg86.u.w.es = PB2BASE(temp_mem.phys); /* set a segment base */
	reg86.u.w.di = PB2OFF(temp_mem.phys); /* set the offset accordingly */
	reg86.u.b.intno = 0x10;

  if( sys_int86(&reg86) != OK ) {
    printf("\tvg_exit(): sys_int86() failed \n");
    return 1;
  }

  memcpy(vmi_p, temp_mem.virt, 256);

	lm_free(&temp_mem);

  return 1;
}
