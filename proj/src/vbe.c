#include "lcom/lcf.h"
#include "videomacros.h"
#include "vbe.h"

int vbe_get_info_mode(unsigned short mode, vbe_mode_info_t *vmi_p)
{
    struct reg86u reg86;
    mmap_t mm;
    if(lm_init(true)== NULL)
        lm_init(true);
    lm_alloc(sizeof(vmi_p), &mm);    
  
    memset(&reg86, 0, sizeof(reg86));        /* zero the structure */
    reg86.u.b.intno = VIDEO_CARD_INT_NO;     /* BIOS video services */
    reg86.u.b.ah = VBE_FUNCTION;             /* invoking VBE function */
    reg86.u.b.al = VBE_MODE_INFO;            /* Return VBE Mode Information*/
    reg86.u.w.cx = mode;
    reg86.u.w.es = PB2BASE(mm.phys);
    reg86.u.w.di = PB2OFF(mm.phys) ;

    //temporarily switches from 32-bit protected mode to 16-bit real-mode to access the BIOS calls
    if (sys_int86(&reg86) != OK) { // if Operation fail
        lm_free(&mm);
        printf("vg_init(): sys_int86() failed \n");
        return 1;
    }
        
    *vmi_p = *(vbe_mode_info_t *) mm.virt;

    if(lm_free(&mm) == 0)
        return 1;
	    
    return 0;
}

