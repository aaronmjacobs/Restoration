#include "AnimHelper.h"
#include "Loader.h"
#include "Mesh.h"
#include "Model.h"
#include "Particle.h"
#include "Scene.h"
#include "SceneGraph.h"

SPtr<Model> Particle::particleModel;
SPtr<Model> Particle::stencilParticleModel;

void Particle::initialize(SPtr<Scene> scene) {
   Loader &loader = Loader::getInstance();

   SPtr<Mesh> mesh = std::make_shared<Mesh>("data/meshes/particle.obj");
   SPtr<Material> particleMaterial = loader.loadMaterial(scene, "particle");
   SPtr<Material> simpleMaterial = loader.loadMaterial(scene, "simple");

   particleModel = std::make_shared<Model>(particleMaterial, mesh);
   stencilParticleModel = std::make_shared<Model>(simpleMaterial, mesh);
}

void Particle::createEffect(SPtr<Scene> scene, glm::vec3 position, glm::vec3 velocity, bool gravityOn, float size, int numParts, float duration, float spread, bool stencil) {
   for (int i = 0; i < numParts; i++) {
      SPtr<Particle> particle;
      if (stencil) {
         particle = std::make_shared<Particle>(scene, stencilParticleModel, size);
         particle->setRenderState(STENCIL_STATE);
      } else {
         particle = std::make_shared<Particle>(scene, particleModel, size);
      }

      if (gravityOn) {
         particle->acceleration = glm::vec3(0.0f, -9.8f, 0.0f);
      }
      else {
         particle->acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
      }

      //Spread & Velocity
      particle->position = position;
      particle->velocity = AnimHelper::randomSpherical(spread) + velocity;
      particle->acceleration += AnimHelper::randomSpherical(spread);
      
      particle->duration = duration;
      scene->getSceneGraph()->add(particle);
   }
}

const std::string Particle::CLASS_NAME = "Particle";

Particle::Particle(SPtr<Scene> scene, SPtr<Model> model, float size, const std::string &name)
: Geometry(scene, model, name), size(size) {
   scaleBy(glm::vec3(size));
   shouldBeSerialized(false);
}

Particle::~Particle() {
}

Json::Value Particle::serialize() const {
   Json::Value root;
   return root; // TODO Don't serialize particles
}

void Particle::tick(const float dt) {
   duration -= dt;

   position += velocity * dt + 0.5f * acceleration * dt * dt;
   velocity += acceleration * dt;

   if (duration < 1.0f) {
      setScale(glm::vec3(size * duration));
   }

   if (duration < 0.0f) {
      markForRemoval();
   }
}
