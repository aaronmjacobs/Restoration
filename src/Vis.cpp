#include "CollisionsIncludes.h"

const std::string Vis::CLASS_NAME = "Vis";

Vis::Vis(SPtr<Scene> scene, SPtr<Model> model, int attackPower, const std::string &name)
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
      markForRemoval();
      return;
   }
   lifeTime += dt;

   MovableObject::tick(dt);
}

int Vis::getAttackPower() {
   return attackPower;
}

void Vis::setAttackPower(int attackPower) {
   this->attackPower = attackPower;
}
