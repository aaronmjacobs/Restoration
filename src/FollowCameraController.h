#ifndef FOLLOW_CAMERA_CONTROLLER_H
#define FOLLOW_CAMERA_CONTROLLER_H

#include "TickListener.h"
#include "Types.h"

class Camera;
class SceneObject;

/**
 * Controls a camera (to be a first person perspective) from user input events.
 */
class FollowCameraController : public TickListener {
private:
   WPtr<Camera> camera;
   WPtr<SceneObject> objectToFollow;

public:
   FollowCameraController(SPtr<Camera> camera, SPtr<SceneObject> objectToFollow);
   virtual ~FollowCameraController();

   /**
    * Steps |dt| seconds through time.
    */
   virtual void tick(const float dt);
};

#endif
