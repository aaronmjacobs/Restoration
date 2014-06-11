#include "AnimHelper.h"
#include "Camera.h"
#include "CatmulRomCameraController.h"

CatmulRomCameraController::CatmulRomCameraController(SPtr<Camera> camera, const float animLength, const std::vector<glm::vec3> cameraPoints, const std::vector<glm::vec3> lookAtPoints)
: CameraController(camera), animLength(animLength), cameraPoints(cameraPoints), lookAtPoints(lookAtPoints), animTime(0.0f) {
   ASSERT(!cameraPoints.empty(), "Must have at least 1 camera point");
   ASSERT(!lookAtPoints.empty(), "Must have at least 1 look at point");
}

CatmulRomCameraController::~CatmulRomCameraController() {
}

void CatmulRomCameraController::reset() {
   animTime = 0.0f;
}

void CatmulRomCameraController::tick(const float dt) {
   float time = glm::min(1.0f, animTime / animLength);
   glm::vec3 location = AnimHelper::catmulRom(cameraPoints, time);
   glm::vec3 lookAt = AnimHelper::catmulRom(lookAtPoints, time);

   SPtr<Camera> sCamera = camera.lock();
   if (sCamera) {
      sCamera->setPosition(location);
      sCamera->setLookAt(lookAt);
   }

   animTime += dt;
}
