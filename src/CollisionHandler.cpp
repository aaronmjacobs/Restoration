#include "CollisionHandler.h"

CollisionHandler::CollisionHandler() {
}

CollisionHandler::~CollisionHandler() {
}

void CollisionHandler::handleCollision(Player *player, Platform *platform) {
   // TODO Handle collision for reals
   AxisAlignedBoundingBox playerBounds = player->getBounds();
   AxisAlignedBoundingBox platformBounds = platform->getBounds();

   float yChange = platformBounds.yMax - playerBounds.yMin;
   player->move(glm::vec3(0.0f, yChange, 0.0f));
}
