#include "Camera.h"

#include <glm/gtc/constants.hpp>
#include <glm/gtx/transform.hpp>

Camera::Camera() {
   position = glm::vec3(0.0f);
   phi = 0.0f;
   theta = -glm::half_pi<float>();

   updateFront();
}

Camera::~Camera() {

}

void Camera::updateFront() {
   front = glm::normalize(glm::vec3(cos(phi) * cos(theta),
                                    sin(phi),
                                    cos(phi) * cos(90.0f - theta)));
}

void Camera::translate(glm::vec3 trans) {
   position += trans;
}

void Camera::fly(float amount) {
   translate(front * amount);
}

void Camera::walk(float amount) {
   glm::vec3 forward = front;
   forward.y = 0.0f;
   forward = glm::normalize(forward);

   translate(forward * amount);
}

void Camera::strafe(float amount) {
  glm::vec3 forward = front;
  forward.y = 0.0f;
  forward = glm::normalize(forward);
  glm::vec3 right = glm::cross(forward, glm::vec3(0.0, 1.0, 0.0));
  
  translate(right * amount);
}

void Camera::rotate(float phi, float theta) {
   // Prevent the camera from looking straight up or down
   if(this->phi + phi < VERT_LOOK_BOUND && this->phi + phi > -VERT_LOOK_BOUND) {
      this->phi += phi;
   }
   this->theta += theta;

   updateFront();
}

glm::mat4 Camera::getViewMatrix() {
  return glm::lookAt(position, // Camera position
                     position + front, // What we're looking at
                     glm::vec3(0.0, 1.0, 0.0)); // Up vector
}
