#include "GLIncludes.h"

#include "CollisionsIncludes.h"

const std::string Justitia::CLASS_NAME = "Justitia";

const int Justitia::ATTACK_POWER = 2;

// Put health in the creation of Magus, and damage
Justitia::Justitia(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: Vis(scene, model, ATTACK_POWER, name) {
}

Justitia::~Justitia() {
}

Json::Value Justitia::serialize() const {
   Json::Value root = Vis::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

void Justitia::tick(const float dt) {
   scale = glm::vec3(0.3f);
   Vis::tick(dt);
}

void Justitia::draw(const RenderData &renderData) {
   if (renderData.getRenderState() == STENCIL_STATE) {
      scale = glm::vec3(2.0f);
   } else {
      scale = glm::vec3(0.3f);
   }

   Vis::draw(renderData);
}

#define COLLISION_CLASS_NAME Justitia
#include "CollisionsBoilerplateCpp.h"
