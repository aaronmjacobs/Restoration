#ifndef FIRST_PERSON_CAMERA_CONTROLLER_H
#define FIRST_PERSON_CAMERA_CONTROLLER_H

#include "engine/Camera.h"
#include "engine/GLIncludes.h"
#include "engine/InputListener.h"
#include "engine/TickListener.h"

/**
 * Controls a camera (to be a first person perspective) from user input events.
 */
class FirstPersonCameraController : public InputListener, public TickListener {
private:
   const static float MOUSE_SCALE;
   CameraRef camera;
   bool forward, backward, left, right;
   bool leftMouse;
   double mouseX, mouseY;

public:
   FirstPersonCameraController(CameraRef camera);
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
