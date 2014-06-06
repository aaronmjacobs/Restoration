#include "CollisionsIncludes.h"
#include "Particle.h"

const std::string Aegrum::CLASS_NAME = "Aegrum";

//Put health in the creation of Magus, and damage
Aegrum::Aegrum(SPtr<Scene> scene, SPtr<Model> model, const float attackPower, const std::string &name)
: Vis(scene, model, attackPower, name) {
   renderState |= SHADOW_STATE;
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
                                false);             // Stencil mode
      }
      markForRemoval();
      return;
   }
   lifeTime += dt;

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
