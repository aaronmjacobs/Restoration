#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "PhysicalObjects/Platform.h"
#include "PhysicalObjects/Player.h"

class CollisionHandler {
private:
   Scene *scene;

public:
   CollisionHandler(Scene *scene);
   virtual ~CollisionHandler();
   void handleCollision(PlayerRef player, PlatformRef platform);
};

#endif
