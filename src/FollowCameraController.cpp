#include "Camera.h"
#include "FollowCameraController.h"
#include "SceneObject.h"

FollowCameraController::FollowCameraController(SPtr<Camera> camera, SPtr<SceneObject> objectToFollow)
: camera(camera), objectToFollow(objectToFollow) {
   camera->setRotation(-0.2f, -1.45f);
   glm::vec3 pos = objectToFollow->getPosition();
   pos.z = 10.0f;
   pos.x += 0.5f;
   camera->setPosition(pos);
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

   glm::vec3 newCameraPos(cameraPos + (move * dt));
   newCameraPos.z = 10.0f;

   sCamera->setRotation(-0.2f, -1.45f); // TODO
   sCamera->setPosition(newCameraPos);
}
