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

float Vis::getAttackPower() {
   return attackPower;
}

void Vis::setAttackPower(float attackPower) {
   this->attackPower = attackPower;
}
