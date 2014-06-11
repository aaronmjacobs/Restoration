#ifndef CATMUL_ROM_CAMERA_CONTROLLER_H
#define CATMUL_ROM_CAMERA_CONTROLLER_H

#include "CameraController.h"
#include "TickListener.h"
#include "Types.h"

#include <vector>

class Camera;

class CatmulRomCameraController : public CameraController {
private:
   const float animLength;
   const std::vector<glm::vec3> cameraPoints, lookAtPoints;
   float animTime;

public:
   CatmulRomCameraController(SPtr<Camera> camera, const float animLength, const std::vector<glm::vec3> cameraPoints, const std::vector<glm::vec3> lookAtPoints);
   virtual ~CatmulRomCameraController();

   virtual void reset();

   bool doneAnimating();

   /**
    * Steps |dt| seconds through time.
    */
   virtual void tick(const float dt);
};

#endif
