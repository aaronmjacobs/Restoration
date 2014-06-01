#include "AnimHelper.h"
#include "LifeParticle.h"
#include "Loader.h"
#include "Material.h"
#include "Mesh.h"
#include "Model.h"
#include "Player.h"
#include "Scene.h"
#include "SceneGraph.h"

const std::string LifeParticle::CLASS_NAME = "LifeParticle";

const float LifeParticle::MAX_FOLLOW_SPEED = 200.0f;

void LifeParticle::createEffect(SPtr<Scene> scene, glm::vec3 position, glm::vec3 velocity, float size, int numParts, float duration, float spread, float healthAmount) {
   for (int i = 0; i < numParts; i++) {
      SPtr<LifeParticle> particle = std::make_shared<LifeParticle>(scene, size, healthAmount / numParts);
      particle->setRenderState(STENCIL_STATE);

      //Spread & Velocity
      particle->velocity = AnimHelper::randomSpherical(spread) + velocity;
      particle->acceleration = AnimHelper::randomSpherical(spread) * 3.0f;
      particle->position = AnimHelper::randomSpherical(spread / 4.0f) + position;

      particle->duration = duration;
      scene->getSceneGraph()->add(particle);
   }
}

LifeParticle::LifeParticle(SPtr<Scene> scene, float size, float healthAmount, const std::string &name)
: Particle(scene, stencilParticleModel, size, name), timeAlive(0.0f), healthAmount(healthAmount) {
}

LifeParticle::~LifeParticle() {
}

void LifeParticle::tick(const float dt) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      SPtr<Player> player = sScene->getPlayer().lock();
      if (player) {
         glm::vec3 playerPos = player->getPosition();
         glm::vec3 toPlayer = playerPos - position;

         float toPlayerLength = glm::length(toPlayer);
         if (toPlayerLength < player->getAuraRadius()) {
            player->setHealth(player->getHealth() + healthAmount);
            markForRemoval();
         }
         if (toPlayerLength < 1.0f) {
            toPlayerLength = 1.0f;
         }

         float speed = MAX_FOLLOW_SPEED / (toPlayerLength * toPlayerLength);
         if (speed < 1.0f) {
            speed = 1.0f;
         }
         float timeAdjust = glm::min(timeAlive, 2.0f) / 2.0f;
         timeAdjust = timeAdjust * timeAdjust;
         acceleration = timeAdjust * ((toPlayer * speed) - velocity) + (1.0f - timeAdjust) * acceleration;
      }
   }

   timeAlive += dt;
   Particle::tick(dt);
}