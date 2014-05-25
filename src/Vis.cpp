#include "CollisionsIncludes.h"

const std::string Vis::CLASS_NAME = "Vis";

Vis::Vis(SPtr<Scene> scene, SPtr<Model> model, int attackPower, const std::string &name)
: MovableObject(scene, model, name),  attackPower(attackPower){
}

Vis::~Vis() {
}

Json::Value Vis::serialize() const {
   Json::Value root = MovableObject::serialize();

   root["@class"] = CLASS_NAME;

   //root["attackPower"] = attackPower;

   return root;
}

void Vis::removeVis() {
   markForRemoval();
}

int Vis::getAttackPower() {
   return attackPower;
}

//Set velocity when attacking with Player. Direction is based on velocity
void Vis::tick(const float dt) {
   position += velocity * dt;
}