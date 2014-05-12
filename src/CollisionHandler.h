#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "Types.h"

class Corona;
class Enemy;
class Magus;
class MovableObject;
class PhysicalObject;
class Player;
class Scene;
class Scenery;
class Character;
class Vis;
class Justitia;
class Aegrum;

//class MovingPlatform

class CollisionHandler {
protected:
   Scene &scene;

public:
   CollisionHandler(Scene &scene);
   virtual ~CollisionHandler();

   void handleCollision(Scenery &first, PhysicalObject &second);

    void handleCollision(MovableObject &first, MovableObject &second);
    void handleCollision(Player &player, Enemy &enemy);
    void handleCollision(Player &player, Magus &magus);
    void handleCollision(Player &player, Corona &corona);
    void handleCollision(Enemy &enemy1, Enemy &enemy2);
    void handleCollision(Character &character, Scenery &scenery);
   /* void handleCollision(movingPlatform &movingPlatform, Platform &platform);*/
    void handleCollision(Vis &vis, Scenery &scenery);
    void handleCollision(Justitia &justitia, Enemy &enemy);
    void handleCollision(Aegrum &aegrum, Player &player);
    //Incase we want to do a shiny collision explosion
    void handleCollision(Justitia &justitia, Aegrum &aegrum);

};

#endif
