#include "FirstPersonCameraController.h"

const float FirstPersonCameraController::MOUSE_SCALE = 0.005f;

FirstPersonCameraController::FirstPersonCameraController(Camera *camera)
   : camera(camera) {
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
   // Update camera orientation
   if (leftMouse) {
      float dPhi = -(yPos - mouseY) * MOUSE_SCALE;
      float dTheta = (xPos - mouseX) * MOUSE_SCALE;
      camera->rotate(dPhi, dTheta);
   }

   mouseX = xPos;
   mouseY = yPos;
}

void FirstPersonCameraController::tick(const float dt) {
   // Camera motion
   if (forward) {
      camera->fly(dt);
   }
   if (backward) {
      camera->fly(-dt);
   }
   if (right) {
      camera->strafe(dt);
   }
   if (left) {
      camera->strafe(-dt);
   }
}
