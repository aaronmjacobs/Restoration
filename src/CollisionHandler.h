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
   bool playerWon;

public:
   CollisionHandler(Scene &scene);
   virtual ~CollisionHandler();

   void handleCollision(PhysicalObject &first, PhysicalObject &second);
   void handleCollision(Player &player, Enemy &enemy);
   void handleCollision(Player &player, Spike &spike);
   COLLISION_REVERSE_DECLARATION(Player, Spike)
   void handleCollision(Character &character, Scenery &scenery);
   COLLISION_REVERSE_DECLARATION(Character, Scenery)
   void handleCollision(Obex &obex, Scenery &scenery);
   COLLISION_REVERSE_DECLARATION(Obex, Scenery)
   void handleCollision(Justitia &justitia, Scenery &scenery);
   COLLISION_REVERSE_DECLARATION(Justitia, Scenery)
   void handleCollision(Aegrum &aegrum, Scenery &scenery);
   COLLISION_REVERSE_DECLARATION(Aegrum, Scenery)
   void handleCollision(Justitia &justitia, Aegrum &aegrum);
   COLLISION_REVERSE_DECLARATION(Justitia, Aegrum)
   void handleCollision(Corona &corona, Scenery &scenery);
   COLLISION_REVERSE_DECLARATION(Corona, Scenery)

   void handleCollision(Justitia &justitia, Enemy &enemy);
   COLLISION_REVERSE_DECLARATION(Justitia, Enemy)
   void handleCollision(Aegrum &aegrum, Player &player);
   COLLISION_REVERSE_DECLARATION(Aegrum, Player)

   void handleCollision(Player &player, Checkpoint &checkpoint);
   COLLISION_REVERSE_DECLARATION(Player, Checkpoint)
};

#endif
