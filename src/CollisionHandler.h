#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "Types.h"

class MovableObject;
class Scene;

class CollisionHandler {
protected:
   Scene &scene;

public:
   CollisionHandler(Scene &scene);
   virtual ~CollisionHandler();

   void handleCollision(MovableObject &first, MovableObject &second);
};

#endif
