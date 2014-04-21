#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "PhysicalObjects/Platform.h"
#include "PhysicalObjects/Player.h"

class CollisionHandler {
public:
   CollisionHandler();
   virtual ~CollisionHandler();
   void handleCollision(Player *player, Platform *platform);
};

#endif
