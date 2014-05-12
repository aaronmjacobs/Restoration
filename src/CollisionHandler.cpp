#include "CollisionHandler.h"
#include "MovableObject.h"
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Magus.h"
#include "Corona.h"
#include "Scenery.h"

CollisionHandler::CollisionHandler(Scene &scene)
   : scene(scene) {
}

CollisionHandler::~CollisionHandler() {
}

void handleCollision(PhysicalObject &first, PhysicalObject &second) {
   // Default handler, does nothing
}

void CollisionHandler::handleCollision(Scenery &first, PhysicalObject &second) {
   // TODO Handle collision between an arbitrary immobile object, and an arbitrary mobile object
}

void CollisionHandler::handleCollision(MovableObject &first, MovableObject &second) {
   std::cout << "Colliding" << std::endl;
    
    
}

void CollisionHandler::handleCollision(Player &player, Enemy &enemy) {
    std::cout << "Colliding with an enemy" << std::endl;
}

void CollisionHandler::handleCollision(Player &player, Magus &magus) {
    player.Character::setHealth(player.getHealth() - magus.getAttackPower());
}

void CollisionHandler::handleCollision(Player &player, Corona &corona) {
    player.Character::setHealth(player.getHealth() - corona.getAttackPower());
    corona.reverseMovement();
    //Add enemy logic for backing off after hurting you
}


void CollisionHandler::handleCollision(Enemy &enemy1, Enemy &enemy2) {
    //Reverse direction
    enemy1.reverseMovement();
    enemy2.reverseMovement();
}

void CollisionHandler::handleCollision(Character &character, Scenery &scenery) {
    BoundingBox collision = BoundingBox(character.getBounds(), scenery.getBounds());
    float collisionWidth = collision.width();
    float collisionHeight = collision.height();
    glm::vec3 movementChange = glm::vec3(0.0f);
    glm::vec3 velocityChange = glm::vec3(0.0f);
    
    if (collisionWidth <= collisionHeight) {
        if (character.getPosition().x > scenery.getPosition().x) {
            //Hit from the right
            movementChange = glm::vec3(collisionWidth, 0.0f, 0.0f);
        } else {
            //Hit from the left
            movementChange = glm::vec3(-collisionWidth, 0.0f, 0.0f);
        }
        velocityChange = glm::vec3(0.0f, character.getVelocity().y, 0.0f);
    } else {
        if (character.getPosition().y > scenery.getPosition().y) {
            //Hit from above
            movementChange = glm::vec3(0.0f, collisionHeight, 0.0f);
            
            character.setOnGround();
        } else {
            //Hit from below
            movementChange = glm::vec3(0.0f, -collisionHeight, 0.0f);
        }
        velocityChange = glm::vec3(character.getVelocity().x, 0.0f, 0.0f);
    }
    character.translateBy(movementChange);
    character.setVelocity(velocityChange);
}

/*
void CollisionHandler::handleCollision(movingPlatform &movingPlatform, Scenery &scenery) {
    //Reverse moving direction
}

void CollisionHandler::handleCollision(Bullet &bullet, Scenery &scenery) {
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