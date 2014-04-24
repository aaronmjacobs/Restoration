#include "FollowCameraController.h"

FollowCameraController::FollowCameraController(CameraRef camera, PlayerRef player)
   : camera(camera), player(player) {
}

FollowCameraController::~FollowCameraController() {
}

void FollowCameraController::tick(const float dt) {
   glm::vec3 playerPos = player->getPosition();
   glm::vec3 cameraPos = camera->getPosition();

   glm::vec3 toPlayer = playerPos - cameraPos;
   toPlayer.z = 0.0f; // We don't want the camera to move in z

   float toPlayerLen = glm::length(toPlayer);
   float moveLen = glm::max(toPlayerLen, toPlayerLen * toPlayerLen);
   glm::vec3 move = glm::normalize(toPlayer) * moveLen;

   camera->setPosition(cameraPos + (move * dt));
}
