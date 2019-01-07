#include "lcom/lcf.h"
#include "collision.h"
#include "minixforce.h"

CollisionArea* newCollisionArea(int x1, int y1, int x2, int y2) {

  CollisionArea* collider = (CollisionArea*) malloc(sizeof(CollisionArea));

  /* top left corner */
	collider->x1 = x1;
	collider->y1 = y1;

	/* right bottom corner*/
	collider->x2 = x2;
	collider->y2 = y2;

  return collider;
}

int collision(CollisionArea* c1, CollisionArea* c2) {

  /* c1 is right of c2 */
  if (c1->x1 > c2->x2)
    return 0;
  /* c1 is left of c2 */
  if (c1->x2 < c2->x1)
    return 0;
  /* c1 is on top of c2 */
  if (c1->y1 > c2->y2)
    return 0;
  /* c1 is under c2 */
  if (c1->y2 < c2->y1)
    return 0;

  /* If neither of the past conditions are met, there has been a collision */
  return 1;
}

void deleteAllCollisionAreas() {
  MinixForce* game = getGame();

  /* Delete soldier CollisionArea */
  deleteCollisionArea(game->soldier->body);

  /* Delete zombies CollisionArea */
  for (int i = 0; i < NUMBER_OF_ZOMBIES; i++) {
    deleteCollisionArea(game->zombies[i]->body);
  }

  /* Delete shots CollisionArea */
  for (int i = 0; i < MAX_NUMBER_OF_SHOTS; i++) {
    deleteCollisionArea(game->shots[i]->body);
  }
}

void deleteCollisionArea(CollisionArea* collider) {
	free(collider);
}
