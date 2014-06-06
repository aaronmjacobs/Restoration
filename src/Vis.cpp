#include "CollisionsIncludes.h"
#include "Particle.h"

const std::string Vis::CLASS_NAME = "Vis";

Vis::Vis(SPtr<Scene> scene, SPtr<Model> model, const float attackPower, const std::string &name)
: MovableObject(scene, model, name), attackPower(attackPower), lifeTime(0.0f) {
}

Vis::~Vis() {
}

Json::Value Vis::serialize() const {
   Json::Value root = MovableObject::serialize();

   root["@class"] = CLASS_NAME;

   root["attackPower"] = attackPower;

   return root;
}

void Vis::tick(const float dt) {
   if (lifeTime > LIFE_SECONDS) {
      SPtr<Scene> sScene = scene.lock();
      if (sScene) {
         Particle::createEffect(sScene,
                                getPosition(),     // Position
                                glm::vec3(0.0f),   // Velocity
                                false,             // Gravity enabled
                                5.0f,              // Size
                                10,                // Number of particles
                                3.0f,              // Duration (seconds)
                                25.0f,             // Particle spread
                                true);             // Stencil mode
      }
      markForRemoval();
      return;
   }
   lifeTime += dt;

   MovableObject::tick(dt);
}

float Vis::getAttackPower() {
   return attackPower;
}

void Vis::setAttackPower(float attackPower) {
   this->attackPower = attackPower;
}
