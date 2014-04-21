#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "PhysicalObjects/Platform.h"
#include "PhysicalObjects/Player.h"

class CollisionHandler {
protected:
   AxisAlignedBoundingBox genCollisionBox(AxisAlignedBoundingBox first, AxisAlignedBoundingBox second);
public:
   CollisionHandler();
   virtual ~CollisionHandler();
   void handleCollision(Player *player, Platform *platform);
};

#endif
