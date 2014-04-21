#ifndef FOLLOW_CAMERA_CONTROLLER_H
#define FOLLOW_CAMERA_CONTROLLER_H

#include "engine/Camera.h"
#include "engine/TickListener.h"
#include "PhysicalObjects/Player.h"

class FollowCameraController : public TickListener {
private:
   CameraRef camera;
   PlayerRef player;

public:
   FollowCameraController(CameraRef camera, PlayerRef player);
   virtual ~FollowCameraController();

   /**
    * Steps |dt| seconds through time.
    */
   virtual void tick(const float dt);
};

#endif
