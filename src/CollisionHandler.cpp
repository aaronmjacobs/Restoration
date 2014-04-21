#include "CollisionHandler.h"

CollisionHandler::CollisionHandler() {
}

CollisionHandler::~CollisionHandler() {
}

void CollisionHandler::handleCollision(Player *player, Platform *platform) {
   // TODO Handle collision for reals
   AxisAlignedBoundingBox playerBounds = player->getBounds();
   AxisAlignedBoundingBox platformBounds = platform->getBounds();
   AxisAlignedBoundingBox collision = genCollisionBox(playerBounds, platformBounds);
   float collisionWidth = collision.xMax - collision.xMin;
   float collisionHeight = collision.yMax - collision.yMin;

   glm::vec3 playerPos = player->getPosition();
   glm::vec3 platformPos = platform->getPosition();
   glm::vec3 playerVel = player->getVelocity();
   glm::vec3 playerMove(0.0f);

   if (collisionWidth <= collisionHeight) {
      // Treat the collision in x
      if (playerPos.x >= platformPos.x) {
         // Player is to the right
         playerMove.x = collisionWidth;
         if (playerVel.x < 0.0f) {
            playerVel.x = 0.0f;
         }
      } else {
         // Player is to the left
         playerMove.x = -collisionWidth;
         if (playerVel.x > 0.0f) {
            playerVel.x = 0.0f;
         }
      }
   } else {
      // Treat the collision in y
      if (playerPos.y >= platformPos.y) {
         // Player is above
         playerMove.y = collisionHeight;
         player->setOnGround();
         if (playerVel.y < 0.0f) {
            playerVel.y = 0.0f;
         }
      } else {
         // Player is below
         playerMove.y = -collisionHeight;
         if (playerVel.y > 0.0f) {
            playerVel.y = 0.0f;
         }
      }
   }

   player->move(playerMove);
   player->setVelocity(playerVel);
}

AxisAlignedBoundingBox CollisionHandler::genCollisionBox(AxisAlignedBoundingBox first, AxisAlignedBoundingBox second) {
   AxisAlignedBoundingBox collision;

   collision.xMin = glm::max(first.xMin, second.xMin);
   collision.xMax = glm::min(first.xMax, second.xMax);
   collision.yMin = glm::max(first.yMin, second.yMin);
   collision.yMax = glm::min(first.yMax, second.yMax);

   return collision;
}