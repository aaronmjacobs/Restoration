#include "AnimHelper.h"
#include "Loader.h"
#include "Mesh.h"
#include "Model.h"
#include "Particle.h"
#include "Scene.h"
#include "SceneGraph.h"

SPtr<Model> Particle::particleModel;

void Particle::initialize(SPtr<Scene> scene) {
   Loader &loader = Loader::getInstance();
   SPtr<Mesh> mesh = std::make_shared<Mesh>("data/meshes/particle.obj");
   SPtr<Material> material = loader.loadMaterial(scene, "particle");
   particleModel = std::make_shared<Model>(material, mesh);
}

void Particle::createEffect(SPtr<Scene> scene, glm::vec3 position, glm::vec3 velocity, bool gravityOn, float size, int numParts, float duration, float spread) {
   for (int i = 0; i < numParts; i++) {
      SPtr<Particle> particle = std::make_shared<Particle>(scene);

      if (gravityOn) {
         particle->acceleration = glm::vec3(0.0f, -9.8f, 0.0f);
      }
      else {
         particle->acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
      }

      //Spread & Velocity
      particle->velocity = AnimHelper::randomSpherical(spread) + velocity;
      particle->acceleration += AnimHelper::randomSpherical(spread);

      particle->scaleBy(glm::vec3(size));
      
      particle->duration = duration;
      scene->getSceneGraph()->add(particle);
   }
}

const std::string Particle::CLASS_NAME = "Particle";

Particle::Particle(SPtr<Scene> scene, const std::string &name)
:  Geometry(scene, particleModel, name) {
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

   if (duration < 0.0f) {
      markForRemoval();
   }
}
