#ifndef _VBE_H
#define _VBE_H

#include <stdint.h>

/** @defgroup vbe vbe
 * @{
 *
 * Basic functions to work with MINIX in graphics mode
 */

/**
 * @brief
 * 
 * @param mode
 * @param vmi_p
 */
int vbe_get_info_mode(unsigned short mode, vbe_mode_info_t *vmi_p);

/**@}*/

#endif /* _VBE_H */
