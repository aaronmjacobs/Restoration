#include "CollisionHandler.h"

CollisionHandler::CollisionHandler(Scene *scene)
   : scene(scene) {
}

CollisionHandler::~CollisionHandler() {
}

void CollisionHandler::handleCollision(PlayerRef player, PlatformRef platform) {
   // TODO Handle collision for reals
   AxisAlignedBoundingBox playerBounds = player->getBounds();
   AxisAlignedBoundingBox platformBounds = platform->getBounds();

   float yChange = platformBounds.yMax - playerBounds.yMin;
   player->move(glm::vec3(0.0f, yChange, 0.0f));
}
