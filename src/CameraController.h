#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "InputListener.h"
#include "TickListener.h"
#include "Types.h"

class Camera;

class CameraController : public TickListener, public InputListener {
protected:
   WPtr<Camera> camera;
   float fade;

public:
   CameraController(SPtr<Camera> camera);
   virtual ~CameraController();

   virtual void reset() = 0;

   float getFade() {
      return fade;
   }

   /**
    * Steps |dt| seconds through time.
    */
   virtual void tick(const float dt);

   /**
    * Called on keyboard events.
    */
   virtual void onKeyEvent(int key, int action);

   /**
    * Called on mouse button click events.
    */
   virtual void onMouseButtonEvent(int button, int action);

   /**
    * Called on mouse motion events.
    */
   virtual void onMouseMotionEvent(double xPos, double yPos);
};

#endif
