#include "CollisionsIncludes.h"

const std::string Spike::CLASS_NAME = "Spike";

const float Spike::ATTACK_POWER = 10.0f;

Spike::Spike(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: Scenery(scene, model, name) {
}

Spike::~Spike() {
}

Json::Value Spike::serialize() const {
   Json::Value root = PhysicalObject::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

#define COLLISION_CLASS_NAME Spike
#include "CollisionsBoilerplateCpp.h"
