#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "Types.h"

class Camera;

class CameraController {
protected:
   WPtr<Camera> camera;
   bool enabled;

public:
   CameraController(SPtr<Camera> camera);
   virtual ~CameraController();

   void setEnabled(bool enabled);
   bool isEnabled();
};

#endif
