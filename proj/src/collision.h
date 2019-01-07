#ifndef _COLLISION_H_
#define _COLLISION_H_

/** @defgroup collision collision
 * @{
 *
 * Basic functions to operate with collisions of game entities.
 */

typedef struct{
	int x1,y1;  /**< @brief coordinates of upper left point of sprite */
  int x2,y2;  /**< @brief coordinates of lower right point of sprite */
} CollisionArea;

/**
 * @brief Creates and allocates memory for a new CollisionArea with the coordinates passed as argument
 * 
 * @param x1 X value of upper left coordinate of a sprite
 * @param y1 Y value of upper left coordinate of a sprite
 * @param x2 X value of lower right coordinate of a sprite
 * @param y2 Y value of lower right coordinate of a sprite
 * 
 * @return CollisionArea Pointer
 */
CollisionArea* newCollisionArea(int x1, int y1, int x2, int y2);

/**
 * @brief Checks if a CollisionArea collided with another
 *
 * @param c1 first CollisionArea pointer
 * @param c2 second CollisionArea pointer
 *
 * @return 1 if there is collision, 0 otherwise 
 */
int collision(CollisionArea* c1, CollisionArea* c2);

/**
 * @brief deletes all CollisionAreas allocated in memory
 */
void deleteAllCollisionAreas();

/**
 * @brief Deletes the CollisionArea passed as argument
 *
 * @param collider CollisionArea pointer to delete
 */
void deleteCollisionArea(CollisionArea* collider);

/**@}*/

#endif  /* _COLLISION_H */
