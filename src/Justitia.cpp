#include "AnimHelper.h"
#include "GLIncludes.h"

#include "CollisionsIncludes.h"

const std::string Justitia::CLASS_NAME = "Justitia";

// Put health in the creation of Magus, and damage
Justitia::Justitia(SPtr<Scene> scene, SPtr<Model> model, const float attackPower, const std::string &name)
: Vis(scene, model, attackPower, name) {
   lifeTime = 0.0f;
}

Justitia::~Justitia() {
}

Json::Value Justitia::serialize() const {
   Json::Value root = Vis::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

void Justitia::tick(const float dt) {
   lifeTime += dt;
   scale = glm::vec3(0.3f);
   Vis::tick(dt);
}

void Justitia::draw(const RenderData &renderData) {
   if (renderData.getRenderState() == STENCIL_STATE) {
      float lifePercent = glm::min<float>(1.0f, lifeTime / 0.5f);
      float scaleAmount = glm::sin(lifePercent * glm::pi<float>() / 2.0f);
      scale = glm::vec3(scaleAmount);
   } else {
      scale = glm::vec3(0.3f);
   }

   Vis::draw(renderData);
}

#define COLLISION_CLASS_NAME Justitia
#include "CollisionsBoilerplateCpp.h"
