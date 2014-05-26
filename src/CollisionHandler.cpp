#include "CollisionHandler.h"
#include "CollisionsIncludes.h"

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

void CollisionHandler::handleCollision(Character &character, Scenery &scenery) {    BoundingBox collision = BoundingBox(character.getBounds(), scenery.getBounds());
   float collisionWidth = collision.width();
   float collisionHeight = collision.height();
   glm::vec3 characterPos = character.getPosition();
   glm::vec3 sceneryPos = scenery.getPosition();
   glm::vec3 characterVel = character.getVelocity();
   glm::vec3 characterMove(0.0f);

   if (collisionWidth <= collisionHeight) {
      // Treat the collision in x
      if (characterPos.x >= sceneryPos.x) {
         // Character is to the right
         characterMove.x = collisionWidth;
         if (characterVel.x < 0.0f) {
            characterVel.x = 0.0f;
         }
      } else {
         // Character is to the left
         characterMove.x = -collisionWidth;
         if (characterVel.x > 0.0f) {
            characterVel.x = 0.0f;
         }
      }
   } else {
      // Treat the collision in y
      if (characterPos.y >= sceneryPos.y) {
         // Character is above
         characterMove.y = collisionHeight;
         character.setOnGround();
         if (characterVel.y < 0.0f) {
            characterVel.y = 0.0f;
         }
      } else {
         // Character is below
         characterMove.y = -collisionHeight;
         if (characterVel.y > 0.0f) {
            characterVel.y = 0.0f;
         }
      }
   }

   character.translateBy(characterMove);
   character.setVelocity(characterVel);
}

COLLISION_REVERSE_FUNCTION(Character, Scenery)

void CollisionHandler::handleCollision(Vis &vis, Scenery &scenery) {
   vis.markForRemoval();
}

COLLISION_REVERSE_FUNCTION(Vis, Scenery)
