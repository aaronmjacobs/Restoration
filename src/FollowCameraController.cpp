#include "Camera.h"
#include "FollowCameraController.h"
#include "SceneObject.h"

FollowCameraController::FollowCameraController(SPtr<Camera> camera, SPtr<SceneObject> objectToFollow)
: camera(camera), objectToFollow(objectToFollow) {
}

FollowCameraController::~FollowCameraController() {
}

void FollowCameraController::tick(const float dt) {
   SPtr<Camera> sCamera = camera.lock();
   SPtr<SceneObject> sObjectToFollow = objectToFollow.lock();
   if (!sCamera || !sObjectToFollow) {
      return;
   }

   glm::vec3 objectPos = sObjectToFollow->getPosition();
   glm::vec3 cameraPos = sCamera->getPosition();

   glm::vec3 toObject = objectPos - cameraPos;
   toObject.z = 0.0f; // We don't want the camera to move in z

   float toObjectLen = glm::length(toObject);
   float moveLen = glm::max(toObjectLen, toObjectLen * toObjectLen);
   glm::vec3 move = glm::normalize(toObject) * moveLen;

   sCamera->setPosition(cameraPos + (move * dt));
}