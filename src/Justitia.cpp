#include "AnimHelper.h"
#include "GLIncludes.h"
#include "Particle.h"

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
                                true);             // Stencil mode
      }
      markForRemoval();
      return;
   } else {

      SPtr<Scene> sScene = scene.lock();
      if (sScene) {
         Particle::createEffect(sScene,
                                    getPosition(),                // Position
                                    -getVelocity(),              // Velocity
                                    false,
                                    5.0f,                                  // Size
                                    1,   // Number of particles
                                    0.5f,                                 // Duration (seconds)
                                    10.0f,        // Particle spread
                                    true);       // Stencil mode
      }

   }
   lifeTime += dt;

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
