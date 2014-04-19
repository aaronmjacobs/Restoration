#include "Camera.h"

Camera::Camera() {
   position = glm::vec3(0.0f);
   phi = 0.0f;
   theta = -glm::half_pi<float>();

   updateFront();
}

Camera::Camera(glm::vec3 position, float phi, float theta)
   : position(position), phi(phi), theta(theta) {
   updateFront();
}

Camera::~Camera() {
}

Json::Value Camera::serialize() const {
   Json::Value root;

   Json::Value posValue;
   posValue["x"] = position.x;
   posValue["y"] = position.y;
   posValue["z"] = position.z;
   root["position"] = posValue;

   root["phi"] = phi;
   root["theta"] = theta;

   return root;
}

void Camera::updateFront() {
   front = glm::normalize(glm::vec3(glm::cos(phi) * glm::cos(theta),
                                    glm::sin(phi),
                                    glm::cos(phi) * glm::cos(glm::half_pi<float>() - theta)));
}

void Camera::translateBy(glm::vec3 trans) {
   position += trans;
}

void Camera::fly(float amount) {
   translateBy(front * amount);
}

void Camera::walk(float amount) {
   // Remove the vertical component of the front vector
   glm::vec3 forward = front;
   forward.y = 0.0f;
   forward = glm::normalize(forward);

   translateBy(forward * amount);
}

void Camera::strafe(float amount) {
   // Remove the vertival component of the front vector
   glm::vec3 forward = front;
   forward.y = 0.0f;
   forward = glm::normalize(forward);

   // Cross the forward vector to get the right vector
   glm::vec3 right = glm::cross(forward, glm::vec3(0.0, 1.0, 0.0));

   translateBy(right * amount);
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
