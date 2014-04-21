#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "PhysicalObjects/Platform.h"

class Character;
class Enemy;
class Bullet;

class CollisionHandler {
protected:
   AxisAlignedBoundingBox genCollisionBox(AxisAlignedBoundingBox first, AxisAlignedBoundingBox second);
public:
   CollisionHandler();
   virtual ~CollisionHandler();
   void handleCollision(Character *character, Platform *platform);
   void handleCollision(Enemy *enemy, Platform *platform);
   void handleCollision(Player *player, Enemy *enemy);
   void handleCollision(Enemy *enemy, Bullet *bullet);
};

#endif
