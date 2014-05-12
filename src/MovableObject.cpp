#include "MovableObject.h"
#include "Scene.h"

const std::string MovableObject::CLASS_NAME = "MovableObject";

MovableObject::MovableObject(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
   : PhysicalObject(scene, model, name) {
}

MovableObject::~MovableObject() {
}

Json::Value MovableObject::serialize() const {
   Json::Value root = PhysicalObject::serialize();

   root["@class"] = CLASS_NAME;

   // Velocity
   Json::Value velocityValue;
   velocityValue["x"] = velocity.x;
   velocityValue["y"] = velocity.y;
   velocityValue["z"] = velocity.z;
   root["velocity"] = velocityValue;

   // Acceleration
   Json::Value accelerationValue;
   accelerationValue["x"] = acceleration.x;
   accelerationValue["y"] = acceleration.y;
   accelerationValue["z"] = acceleration.z;
   root["acceleration"] = accelerationValue;

   return root;
}

glm::vec3 MovableObject::getVelocity() {
   return velocity;
}

glm::vec3 MovableObject::getAcceleration() {
   return acceleration;
}

void MovableObject::setVelocity(const glm::vec3 &vel) {
   velocity = vel;
}

void MovableObject::setAcceleration(const glm::vec3 &acc) {
   acceleration = acc;
}

void MovableObject::tick(const float dt) {
   position += velocity * dt + 0.5f * acceleration * dt * dt;
   velocity += acceleration * dt;
}
