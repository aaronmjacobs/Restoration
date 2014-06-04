#ifndef FOLLOW_CAMERA_CONTROLLER_H
#define FOLLOW_CAMERA_CONTROLLER_H

#include "CameraController.h"
#include "TickListener.h"
#include "Types.h"

class Camera;
class SceneObject;

/**
 * Controls a camera (to be a first person perspective) from user input events.
 */
class FollowCameraController : public CameraController, public TickListener {
private:
   static const float MAX_DISTANCE_CHANGE;
   WPtr<SceneObject> objectToFollow;
   float zDist, phi, theta;

public:
   FollowCameraController(SPtr<Camera> camera, SPtr<SceneObject> objectToFollow, float zDist, float phi, float theta);
   virtual ~FollowCameraController();

   /**
    * Steps |dt| seconds through time.
    */
   virtual void tick(const float dt);
};

#endif
