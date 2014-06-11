#ifndef CUBIC_BEZIER_CAMERA_CONTROLLER_H
#define CUBIC_BEZIER_CAMERA_CONTROLLER_H

#include "CameraController.h"
#include "TickListener.h"
#include "Types.h"

class Camera;

/**
 * Controls a camera (to be a first person perspective) from user input events.
 */
class CubicBezierCameraController : public CameraController {
private:
   const float animLength;
   const glm::vec3 controlOne, controlTwo, controlThree, controlFour;
   float animTime;

public:
   CubicBezierCameraController(SPtr<Camera> camera, const float animLength, const glm::vec3 controlOne, const glm::vec3 controlTwo, const glm::vec3 controlThree, const glm::vec3 controlFour);
   virtual ~CubicBezierCameraController();

   virtual void reset() {
      //
   }

   /**
    * Steps |dt| seconds through time.
    */
   virtual void tick(const float dt);

   
};

#endif
