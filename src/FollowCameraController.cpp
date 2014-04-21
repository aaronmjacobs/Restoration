#include "FollowCameraController.h"

FollowCameraController::FollowCameraController(CameraRef camera, PlayerRef player)
   : camera(camera), player(player) {
}

FollowCameraController::~FollowCameraController() {
}

void FollowCameraController::tick(const float dt) {
   glm::vec3 playerPos = player->getPosition();
   playerPos.z = camera->getPosition().z;
   camera->setPosition(playerPos);
}
