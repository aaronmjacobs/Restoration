#include "CollisionHandler.h"
#include "Scene.h"
#include "MovableObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Magus.h"
#include "Corona.h"
#include "Scenery.h"

#define COLLISION_REVERSE_FUNCTION(FIRST_CLASS, SECOND_CLASS) \
void CollisionHandler::handleCollision(SECOND_CLASS &second, FIRST_CLASS &first) {\
   handleCollision(first, second);\
}

CollisionHandler::CollisionHandler(Scene &scene)
   : scene(scene) {
}

CollisionHandler::~CollisionHandler() {
}

void CollisionHandler::handleCollision(PhysicalObject &first, PhysicalObject &second) {
   // Default handler, does nothing
}

void CollisionHandler::handleCollision(Player &player, Magus &magus) {
    player.setHealth(player.getHealth() - magus.getAttackPower());
}

void CollisionHandler::handleCollision(Player &player, Corona &corona) {
    player.setHealth(player.getHealth() - corona.getAttackPower());
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

COLLISION_REVERSE_FUNCTION(Character, Scenery)
