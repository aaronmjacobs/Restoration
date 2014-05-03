#include "MovableObject.h"

MovableObject::MovableObject(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
   : PhysicalObject(scene, model, name) {
}

MovableObject::~MovableObject() {
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
