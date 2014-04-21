#include "CollisionHandler.h"

#include "PhysicalObjects/Character.h"
#include "PhysicalObjects/Enemy.h"
#include "PhysicalObjects/Bullet.h"

#include <iostream>

CollisionHandler::CollisionHandler() {
}

CollisionHandler::~CollisionHandler() {
}

void CollisionHandler::handleCollision(Character *character, Platform *platform) {
   // TODO Handle collision for reals
   AxisAlignedBoundingBox characterBounds = character->getBounds();
   AxisAlignedBoundingBox platformBounds = platform->getBounds();
   AxisAlignedBoundingBox collision = genCollisionBox(characterBounds, platformBounds);
   float collisionWidth = collision.xMax - collision.xMin;
   float collisionHeight = collision.yMax - collision.yMin;

   glm::vec3 characterPos = character->getPosition();
   glm::vec3 platformPos = platform->getPosition();
   glm::vec3 characterVel = character->getVelocity();
   glm::vec3 characterMove(0.0f);

   if (collisionWidth <= collisionHeight) {
      // Treat the collision in x
      if (characterPos.x >= platformPos.x) {
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
      if (characterPos.y >= platformPos.y) {
         // Character is above
         characterMove.y = collisionHeight;
         character->setOnGround();
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

   character->translateBy(characterMove);
   character->setVelocity(characterVel);
}

void CollisionHandler::handleCollision(Enemy *character, Platform *platform) {
   // TODO Handle collision for reals
   AxisAlignedBoundingBox characterBounds = character->getBounds();
   AxisAlignedBoundingBox platformBounds = platform->getBounds();
   AxisAlignedBoundingBox collision = genCollisionBox(characterBounds, platformBounds);
   float collisionWidth = collision.xMax - collision.xMin;
   float collisionHeight = collision.yMax - collision.yMin;

   glm::vec3 characterPos = character->getPosition();
   glm::vec3 platformPos = platform->getPosition();
   glm::vec3 characterVel = character->getVelocity();
   glm::vec3 characterMove(0.0f);

   if (collisionWidth <= collisionHeight) {
      // Treat the collision in x
      if (characterPos.x >= platformPos.x) {
         // Character is to the right
         characterMove.x = collisionWidth;
      } else {
         // Character is to the left
         characterMove.x = -collisionWidth;
      }
      characterVel.x *= -1.0f;
   } else {
      // Treat the collision in y
      if (characterPos.y >= platformPos.y) {
         // Character is above
         characterMove.y = collisionHeight;
         character->setOnGround();
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

   character->translateBy(characterMove);
   character->setVelocity(characterVel);
}

void CollisionHandler::handleCollision(Player *player, Enemy *enemy) {

   enemy->die();
   player->loseHealth(1);

   std::cout << "Health remaining: " << player->getHealth() << std::endl;
   if (player->getHealth() <= 0) {
      std::cout << "You died D:" << std::endl;
      exit(0);
   }
}

void CollisionHandler::handleCollision(Enemy *enemy, Bullet *bullet) {
   enemy->die();
   bullet->die();
}

AxisAlignedBoundingBox CollisionHandler::genCollisionBox(AxisAlignedBoundingBox first, AxisAlignedBoundingBox second) {
   AxisAlignedBoundingBox collision;

   collision.xMin = glm::max(first.xMin, second.xMin);
   collision.xMax = glm::min(first.xMax, second.xMax);
   collision.yMin = glm::max(first.yMin, second.yMin);
   collision.yMax = glm::min(first.yMax, second.yMax);

   return collision;
}