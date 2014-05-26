#include "Loader.h"
#include "Mesh.h"
#include "Model.h"
#include "Particle.h"

/*

SPtr<Particle> particle = std::make_shared<Particle>(scene);
particle->setPosition(glm::vec3(18.0f, 15.0f, 0.0f));
particle->scaleBy(glm::vec3(5.0f));
scene->getSceneGraph()->add(particle);

*/

SPtr<Model> Particle::particleModel;

void Particle::initialize(SPtr<Scene> scene) {
   Loader &loader = Loader::getInstance();
   SPtr<Mesh> mesh = std::make_shared<Mesh>("data/meshes/particle.obj");
   SPtr<Material> material = loader.loadMaterial(scene, "particle");
   particleModel = std::make_shared<Model>(material, mesh);
}

const std::string Particle::CLASS_NAME = "Particle";

Particle::Particle(SPtr<Scene> scene, const std::string &name)
:  Geometry(scene, particleModel, name) {
   acceleration = glm::vec3(0.0f, -9.8f, 0.0f);
}

Particle::~Particle() {
}

Json::Value Particle::serialize() const {
   Json::Value root;
   return root; // TODO Don't serialize particles
}

void Particle::tick(const float dt) {
   // Do stuff here

   position += velocity * dt + 0.5f * acceleration * dt * dt;
   velocity += acceleration * dt;
}