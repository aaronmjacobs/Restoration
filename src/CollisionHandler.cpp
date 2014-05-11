#include "CollisionHandler.h"
#include "MovableObject.h"
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Magus.h"
#include "Corona.h"

CollisionHandler::CollisionHandler(Scene &scene)
   : scene(scene) {
}

CollisionHandler::~CollisionHandler() {
}

void CollisionHandler::handleCollision(MovableObject &first, MovableObject &second) {
   std::cout << "Colliding" << std::endl;
}

void CollisionHandler::handleCollision(Player &player, Enemy &enemy) {
    std::cout << "Colliding with an enemy" << std::endl;
}

void CollisionHandler::handleCollision(Player &player, Magus &magus) {
    player.Character::setHealth(player.getHealth() - 1);
    //Have enemy class with a damage argument
}

void CollisionHandler::handleCollision(Player &player, Corona &corona) {
    player.Character::setHealth(player.getHealth() - 4);
    //Have enemy class with a damage argument
}


void CollisionHandler::handleCollision(Enemy &enemy1, Enemy &enemy2) {
    //Reverse direction
}

/*void CollisionHandler::handleCollision(Player &player, Platform &platform) {
    if(!player.Character::isOnGround()) {
        //Make sure player doesn't clip into platform
    }
}

void CollisionHandler::handleCollision(Enemy &enemy, Platform &platform) {
    if(!enemy.Character::isOnGround()) {
        //Make sure player doesn't clip into platform
    }
}

void CollisionHandler::handleCollision(movingPlatform &movingPlatform, Platform &platform) {
    //Reverse moving direction
}

void CollisionHandler::handleCollision(Bullet &bullet, Platform &platform) {
    //Remove bullet from scene, both for players and enemies
}

//Maybe combine these two, just have the bullet class have a damage associated with it
void CollisionHandler::handleCollision(PlayerBullet &pBullet, Enemy &enemy) {
    enemy.Character::setHealth(enemy.getHealth() - 1);
    //Change with bullet damage
    //mark for removal thingie
}

void CollisionHandler::handleCollision(EnemyBullet &eBullet, Player &player) {
    player.Character::setHealth(player.getHealth() - 2);
    //change with enemy class done
}

//Incase we want to do a shiny collision explosion
void CollisionHandler::handleCollision(PlayerBullet &pBullet, EnemyBullet &eBullet) {
    
}*/