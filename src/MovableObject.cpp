#include "MovableObject.h"
#include "Scene.h"

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

void MovableObject::tick(const float dt) {
   position += velocity * dt + 0.5f * acceleration * dt * dt;
   velocity += acceleration * dt;
}

void MovableObject::collideWith(PhysicalObject &other) {
   other.collideWith(*this);
}

void MovableObject::collideWith(MovableObject &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(other, *this);
   }
}
