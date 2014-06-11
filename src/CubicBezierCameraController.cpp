#include "AnimHelper.h"
#include "Camera.h"
#include "CubicBezierCameraController.h"

CubicBezierCameraController::CubicBezierCameraController(SPtr<Camera> camera, const float animLength, const glm::vec3 controlOne, const glm::vec3 controlTwo, const glm::vec3 controlThree, const glm::vec3 controlFour)
: CameraController(camera), animLength(animLength), controlOne(controlOne), controlTwo(controlTwo), controlThree(controlThree), controlFour(controlFour) {
}

CubicBezierCameraController::~CubicBezierCameraController() {
}

void CubicBezierCameraController::tick(const float dt) {
   float time = glm::min(1.0f, animTime / animLength);
   glm::vec3 points[6];
   points[0] = controlOne;
   points[1] = controlOne;
   points[2] = controlTwo;
   points[3] = controlThree;
   points[4] = controlFour;
   points[5] = controlFour;
   glm::vec3 location = AnimHelper::cubicBezier(time, controlOne, controlTwo, controlThree, controlFour);

   SPtr<Camera> sCamera = camera.lock();
   if (sCamera) {
      sCamera->setPosition(location);
   }

   animTime += dt;
}
