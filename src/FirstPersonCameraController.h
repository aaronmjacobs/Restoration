#ifndef FIRST_PERSON_CAMERA_CONTROLLER_H
#define FIRST_PERSON_CAMERA_CONTROLLER_H

#include "CameraController.h"
#include "GLIncludes.h"
#include "InputListener.h"
#include "TickListener.h"
#include "Types.h"

class Camera;

/**
 * Controls a camera (to be a first person perspective) from user input events.
 */
class FirstPersonCameraController : public CameraController, public InputListener, public TickListener {
private:
   const static float MOUSE_SCALE;
   const static float MOVEMENT_SCALE;
   bool forward, backward, left, right;
   bool leftMouse;
   double mouseX, mouseY;

public:
   FirstPersonCameraController(SPtr<Camera> camera);
   virtual ~FirstPersonCameraController();

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

   /**
    * Steps |dt| seconds through time.
    */
   virtual void tick(const float dt);
};

#endif
