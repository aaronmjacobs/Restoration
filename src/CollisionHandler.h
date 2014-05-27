#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "CollisionsDeclarations.h"
#include "Types.h"

class PhysicalObject;
class Scene;

/*
 //// Base coverage:
 MovableObject
 Scenery

 //// Full coverage:
 Player
 Magus
 Corona
 Justitia
 Aegrum
 Scenery
*/

#define COLLISION_REVERSE_DECLARATION(FIRST_CLASS, SECOND_CLASS) \
void handleCollision(SECOND_CLASS &second, FIRST_CLASS &first);

class CollisionHandler {
protected:
   Scene &scene;

public:
   CollisionHandler(Scene &scene);
   virtual ~CollisionHandler();

   void handleCollision(PhysicalObject &first, PhysicalObject &second);
   void handleCollision(Player &player, Magus &magus);
   void handleCollision(Player &player, Corona &corona);
   void handleCollision(Enemy &enemy1, Enemy &enemy2);
   void handleCollision(Character &character, Scenery &scenery);
   COLLISION_REVERSE_DECLARATION(Character, Scenery)
   void handleCollision(Obex &obex, Scenery &scenery);
   COLLISION_REVERSE_DECLARATION(Obex, Scenery)
   void handleCollision(Vis &vis, Scenery &scenery);
   COLLISION_REVERSE_DECLARATION(Vis, Scenery)
   void handleCollision(Corona &corona, Scenery &scenery);
   COLLISION_REVERSE_DECLARATION(Corona, Scenery)
};

#endif
