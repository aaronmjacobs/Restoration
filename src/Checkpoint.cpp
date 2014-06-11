#include "CollisionsIncludes.h"

const std::string Checkpoint::CLASS_NAME = "Checkpoint";

Checkpoint::Checkpoint(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: PhysicalObject(scene, model, name) {
}

Checkpoint::~Checkpoint() {
}

Json::Value Checkpoint::serialize() const {
   Json::Value root = PhysicalObject::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

void Checkpoint::tick(const float dt) {
   PhysicalObject::tick(dt);
   // Do nothing
}

#define COLLISION_CLASS_NAME Checkpoint
#include "CollisionsBoilerplateCpp.h"
