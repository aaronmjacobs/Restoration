#include "Camera.h"
#include "FirstPersonCameraController.h"

const float FirstPersonCameraController::MOUSE_SCALE = 0.005f;
const float FirstPersonCameraController::MOVEMENT_SCALE = 10.0f;

FirstPersonCameraController::FirstPersonCameraController(SPtr<Camera> camera)
   : CameraController(camera) {
   forward = backward = left = right = leftMouse = false;
}

FirstPersonCameraController::~FirstPersonCameraController() {
}

void FirstPersonCameraController::onKeyEvent(int key, int action) {
   // Set camera motion state
   if (action == GLFW_PRESS) {
      if (key == GLFW_KEY_W) {
         forward = true;
      } else if (key == GLFW_KEY_S) {
         backward = true;
      } else if (key == GLFW_KEY_A) {
         left = true;
      } else if (key == GLFW_KEY_D) {
         right = true;
      }
   } else if (action == GLFW_RELEASE) {
      if (key == GLFW_KEY_W) {
         forward = false;
      } else if (key == GLFW_KEY_S) {
         backward = false;
      } else if (key == GLFW_KEY_A) {
         left = false;
      } else if (key == GLFW_KEY_D) {
         right = false;
      }
   }
}

void FirstPersonCameraController::onMouseButtonEvent(int button, int action) {
   if (button == GLFW_MOUSE_BUTTON_LEFT) {
      leftMouse = action == GLFW_PRESS;
   }
}

void FirstPersonCameraController::onMouseMotionEvent(double xPos, double yPos) {
   if (enabled) {
      SPtr<Camera> sCamera = camera.lock();

      // Update camera orientation
      if (leftMouse && sCamera) {
         float dPhi = -(yPos - mouseY) * MOUSE_SCALE;
         float dTheta = (xPos - mouseX) * MOUSE_SCALE;
         sCamera->rotateBy(dPhi, dTheta);
      }
   }

   mouseX = xPos;
   mouseY = yPos;
}

void FirstPersonCameraController::tick(const float dt) {
   if (!enabled) {
      return;
   }

   SPtr<Camera> sCamera = camera.lock();
   if (!sCamera) {
      return;
   }

   float movementSpeed = dt * MOVEMENT_SCALE;

   // Camera motion
   if (forward) {
      sCamera->fly(movementSpeed);
   }
   if (backward) {
      sCamera->fly(-movementSpeed);
   }
   if (right) {
      sCamera->strafe(movementSpeed);
   }
   if (left) {
      sCamera->strafe(-movementSpeed);
   }
}
