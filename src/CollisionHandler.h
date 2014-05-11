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
   /* void handleCollision(movingPlatform &movingPlatform, Platform &platform);
    void handleCollision(Bullet &bullet, Platform &platform);
    void handleCollision(PlayerBullet &pBullet, Enemy &enemy);
    void handleCollision(EnemyBullet &eBullet, Player &player);
    //Incase we want to do a shiny collision explosion
    void handleCollision(PlayerBullet &pBullet, EnemyBullet &eBullet);*/

};

#endif
