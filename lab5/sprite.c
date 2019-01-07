#include <lcom/lcf.h>
#include "sprite.h"
#include "video_gr.h"
#include "macros.h"

/** Creates a new sprite with pixmap "pic", with specified
  * position (within the screen limits) and speed;
  * Does not draw the sprite on the screen
  * Returns NULL on invalid pixmap.
  */

Sprite *create_Sprite(const char *pic[], int x, int y, int xspeed, int yspeed) {

  //allocate space for the "object"
  Sprite *sp = (Sprite *) malloc ( sizeof(Sprite));
  if( sp == NULL ) {
    return NULL;
  }

  // Setting sprite current position
  sp->x = x;
  sp->y = y;
  // Setting sprite current speeed
  sp->xspeed = xspeed;
  sp->yspeed = yspeed;
  
  // read the sprite pixmap
  sp->map = read_xpm(pic, &(sp->width), &(sp->height));
  if( sp->map == NULL ) {
    free(sp);
    return NULL;  
  }

  return sp;
}

void destroy_Sprite(Sprite *sp) {
  if( sp == NULL )
    return;

  if( sp ->map )
    free(sp->map);

  free(sp);
  sp = NULL;  // XXX: pointer is passed by value
              // should do this @ the caller
}


int animate_Sprite(Sprite *sp) {
  // updating coordinates
  sp->x += sp->xspeed;
  sp->y += sp->yspeed;
  // drawing sprite in the new location
  draw_xpm(sp->map, sp->width, sp->height, sp->x, sp->y);

  /*
  if ((counter % (FREQ / fr_rate)) == 0 && speed >= 0)
  {
    //animate_Sprite(sprite);
  }
  else if ((counter * (FREQ / fr_rate)) % abs(speed) == 0 && speed < 0)
  {
    //animate_Sprite(sprite);
  }
  */
  
  return 0;
} 

// Some useful non-visible functions
/*
static int draw_Sprite(Sprite *sp, char *base) {
  return 0;
}


static int check_Collision(Sprite *sp, char *base) {
  return 0;
}*/
