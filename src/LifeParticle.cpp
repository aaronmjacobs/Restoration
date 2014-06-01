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

SPtr<Model> LifeParticle::lifeParticleModel;

void LifeParticle::initialize(SPtr<Scene> scene) {
   Loader &loader = Loader::getInstance();

   SPtr<Mesh> mesh = std::make_shared<Mesh>("data/meshes/particle.obj");
   SPtr<Material> material = loader.loadMaterial(scene, "simple");
   lifeParticleModel = std::make_shared<Model>(material, mesh);
}

void LifeParticle::createEffect(SPtr<Scene> scene, glm::vec3 position, glm::vec3 velocity, float size, int numParts, float duration, float spread) {
   for (int i = 0; i < numParts; i++) {
      SPtr<LifeParticle> particle = std::make_shared<LifeParticle>(scene);
      particle->setRenderState(STENCIL_STATE);

      //Spread & Velocity
      particle->velocity = AnimHelper::randomSpherical(spread) + velocity;
      particle->acceleration = AnimHelper::randomSpherical(spread) * 3.0f;
      particle->position = AnimHelper::randomSpherical(spread / 4.0f) + position;

      particle->scaleBy(glm::vec3(size));

      particle->duration = duration;
      scene->getSceneGraph()->add(particle);
   }
}

LifeParticle::LifeParticle(SPtr<Scene> scene, const std::string &name)
: Particle(scene, lifeParticleModel, name), timeAlive(0.0f) {
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
            // TODO Grow aura?
            player->growAura(0.001f);
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