#include "Camera.h"

const std::string Camera::CLASS_NAME = "Camera";

Camera::Camera(SPtr<Scene> const scene, float fov, const std::string &name)
   : SceneObject(scene, name), fov(fov) {
   phi = 0.0f;
   theta = -glm::half_pi<float>();
   updateFront();
}

Camera::~Camera() {
}

glm::mat4 Camera::getProjectionMatrix() {
   return projectionMatrix;
}

void Camera::onWindowSizeChange(int width, int height) {
   // Update the projection to match the new window size.
   projectionMatrix = glm::perspective(fov, (float)width / height, 0.1f, 100.f);
   windowWidth = width;
   windowHeight = height;
}

int Camera::getWindowHeight() {
   return windowHeight;
}

int Camera::getWindowWidth() {
   return windowWidth;
}

Json::Value Camera::serialize() const {
   Json::Value root = SceneObject::serialize();

   root["@class"] = CLASS_NAME;

   root["phi"] = phi;
   root["theta"] = theta;
   root["fov"] = fov;

   return root;
}

void Camera::updateFront() {
   front = glm::normalize(glm::vec3(glm::cos(phi) * glm::cos(theta),
                                    glm::sin(phi),
                                    glm::cos(phi) * glm::cos(glm::half_pi<float>() - theta)));
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

void Camera::rotateBy(float phi, float theta) {
   // Prevent the camera from looking straight up or down
   if(this->phi + phi < VERT_LOOK_BOUND && this->phi + phi > -VERT_LOOK_BOUND) {
      this->phi += phi;
   }
   this->theta += theta;

   updateFront();
}

void Camera::setRotation(float phi, float theta) {
   this->phi = phi;
   this->theta = theta;

   updateFront();
}

glm::mat4 Camera::getViewMatrix() {
  return glm::lookAt(position, // Camera position
                     position + front, // What we're looking at
                     glm::vec3(0.0, 1.0, 0.0)); // Up vector
}

void Camera::draw(const RenderData &renderData) {
}

void Camera::tick(const float dt) {
}
