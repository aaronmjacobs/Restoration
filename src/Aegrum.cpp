#include "CollisionsIncludes.h"

const std::string Aegrum::CLASS_NAME = "Aegrum";

const int Aegrum::ATTACK_POWER = 2;

//Put health in the creation of Magus, and damage
Aegrum::Aegrum(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: Vis(scene, model, ATTACK_POWER, name) {
}

Aegrum::~Aegrum() {
}

Json::Value Aegrum::serialize() const {
   Json::Value root = Vis::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

void Aegrum::tick(const float dt) {
   scale = glm::vec3(0.3f);
   Vis::tick(dt);
}

void Aegrum::draw(const RenderData &renderData) {
   if (renderData.getRenderState() == STENCIL_STATE) {
      scale = glm::vec3(2.0f);
   } else {
      scale = glm::vec3(0.3f);
   }

   Vis::draw(renderData);
}

#define COLLISION_CLASS_NAME Aegrum
#include "CollisionsBoilerplateCpp.h"
