#include "Loader.h"
#include "Mesh.h"
#include "Model.h"
#include "Particle.h"

SPtr<Model> Particle::particleModel;

void Particle::initialize(SPtr<Scene> scene) {
   Loader &loader = Loader::getInstance();
   SPtr<Mesh> mesh = std::make_shared<Mesh>("data/meshes/particle.obj");
   SPtr<Material> material = loader.loadMaterial(scene, "otherMaterial");
   particleModel = std::make_shared<Model>(material, mesh);
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
   // Do stuff here

   position += velocity * dt + 0.5f * acceleration * dt * dt;
   velocity += acceleration * dt;
}