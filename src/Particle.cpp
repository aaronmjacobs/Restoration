#include "Loader.h"
#include "Mesh.h"
#include "Model.h"
#include "Particle.h"
#include "Scene.h"
#include "SceneGraph.h"
#include <random>

SPtr<Model> Particle::particleModelLight;
SPtr<Model> Particle::particleModelDark;

void Particle::initialize(SPtr<Scene> scene) {
   Loader &loader = Loader::getInstance();

   SPtr<Mesh> mesh = std::make_shared<Mesh>("data/meshes/particle.obj");
   SPtr<Material> material = loader.loadMaterial(scene, "particleLight");
   particleModelLight = std::make_shared<Model>(material, mesh);

   SPtr<Mesh> mesh = std::make_shared<Mesh>("data/meshes/particle.obj");
   SPtr<Material> material = loader.loadMaterial(scene, "particleDark");
   particleModelDark = std::make_shared<Model>(material, mesh);
}

void Particle::createEffect(SPtr<Scene> scene, glm::vec3 position, glm::vec3 velocity, bool gravityOn, float size, int numParts, float duration, float spread) {
   std::default_random_engine generator;
   std::uniform_real_distribution<float> distribution(-1.f, 1.f);

   for (int i = 0; i < numParts; i++) {
      SPtr<Particle> particle = std::make_shared<Particle>(scene);

      if (gravityOn) {
         particle->acceleration = glm::vec3(0.0f, -9.8f, 0.0f);
      }
      else {
         particle->acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
      }

      //Spread & Velocity 
      particle->velocity = glm::vec3(velocity.x + spread*distribution(generator), velocity.y + spread*distribution(generator), velocity.z + spread*distribution(generator));

      particle->setPosition(glm::vec3(position.x, position.y, position.z));
      particle->scaleBy(glm::vec3(size));
      
      particle->duration = duration;
      scene->getSceneGraph()->add(particle);
   }
}

const std::string Particle::CLASS_NAME = "Particle";

Particle::Particle(SPtr<Scene> scene, const std::string &name)
: Geometry(scene, particleModelLight, name) { //TODO: Edit this so you can choose light or dark particle
}

Particle::~Particle() {
}

Json::Value Particle::serialize() const {
   Json::Value root;
   return root; // TODO Don't serialize particles
}

void Particle::tick(const float dt) {
   position += velocity * dt + 0.5f * acceleration * dt * dt;
   velocity += acceleration * dt;

   duration -= dt;
   if (duration < 0.0f) {
      markForRemoval();
   }
}
