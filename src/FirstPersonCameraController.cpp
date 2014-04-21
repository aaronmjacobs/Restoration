#include "FirstPersonCameraController.h"

const float FirstPersonCameraController::MOUSE_SCALE = 0.005f;
const float FirstPersonCameraController::MOVEMENT_SCALE = 10.0f;

FirstPersonCameraController::FirstPersonCameraController(CameraRef camera)
   : camera(camera) {
}

FirstPersonCameraController::~FirstPersonCameraController() {
}

void FirstPersonCameraController::onKeyEvent(int key, int action) {
   // Set camera motion state
   if (action == GLFW_PRESS) {
      if (key == GLFW_KEY_UP) {
         forward = true;
      } else if (key == GLFW_KEY_DOWN) {
         backward = true;
      } else if (key == GLFW_KEY_LEFT) {
         left = true;
      } else if (key == GLFW_KEY_RIGHT) {
         right = true;
      }
   } else if (action == GLFW_RELEASE) {
      if (key == GLFW_KEY_UP) {
         forward = false;
      } else if (key == GLFW_KEY_DOWN) {
         backward = false;
      } else if (key == GLFW_KEY_LEFT) {
         left = false;
      } else if (key == GLFW_KEY_RIGHT) {
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
   float movementSpeed = dt * MOVEMENT_SCALE;

   // Camera motion
   if (forward) {
      camera->fly(movementSpeed);
   }
   if (backward) {
      camera->fly(-movementSpeed);
   }
   if (right) {
      camera->strafe(movementSpeed);
   }
   if (left) {
      camera->strafe(-movementSpeed);
   }
}
