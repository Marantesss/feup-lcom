#include "video_gr.h"

static char *video_mem;           /* Process (virtual) address to which VRAM is mapped */
static char *tmp_video_mem;       /* For double buffering */
static unsigned h_res;            /* Horizontal resolution in pixels */
static unsigned v_res;            /* Vertical resolution in pixels */
static unsigned bits_per_pixel;   /* Number of VRAM bits per pixel */
static unsigned bytes_per_pixel;  /* Number of VRAM bytes per pixel */
vbe_mode_info_t vmi_p;
static unsigned int vram_base;    /* VRAM's physical addresss */
static unsigned int vram_size;    /* VRAM's size, we can also use the frame-buffer size, instead */

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

unsigned get_bytes_per_pixel() {
  return bytes_per_pixel;
}

char *get_tmp_video_mem()
{
  return tmp_video_mem;
}

char *get_video_mem()
{
  return video_mem;
}

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
  tmp_video_mem = (char*) malloc(vram_size);

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

void flip_double_buffer() {
	memcpy(video_mem, tmp_video_mem, vram_size);
}

