#ifndef CAMERA_H
#define CAMERA_H

#include "GLIncludes.h"

#include "GLMIncludes.h"

class Camera {
private:
   const float VERT_LOOK_BOUND = 1.5f;
   glm::vec3 position, front;
   float phi, theta;
   void updateFront();

public:
   Camera();
   ~Camera();
   void translate(glm::vec3 trans);
   void fly(float amount);
   void walk(float amount);
   void strafe(float amount);
   void rotate(float phi, float theta);
   glm::vec3 getPosition() {
      return position;
   }
   glm::vec3 getFront() {
      return front;
   }
   glm::mat4 getViewMatrix();
};

#endif