#include "CollisionsIncludes.h"
#include "Particle.h"

const std::string Checkpoint::CLASS_NAME = "Checkpoint";

Checkpoint::Checkpoint(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: PhysicalObject(scene, model, name) {
   passed = false;
}

Checkpoint::~Checkpoint() {
}

Json::Value Checkpoint::serialize() const {
   Json::Value root = PhysicalObject::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

void Checkpoint::tick(const float dt) {
   PhysicalObject::tick(dt);
   if (passed) {
      Particle::createEffect(getScene().lock(),
                             position,    // Position
                             glm::vec3(0.0f),         // Velocity
                             false,                   // Gravity enabled
                             15.0f,                    // Size
                             2,                      // Number of particles
                             1.0f,                    // Duration (seconds)
                             10.0f,                   // Particle spread
                             true);                   // Stencil mode
   }
}

void Checkpoint::trigger() {
   passed = true;
}

void Checkpoint::draw(const RenderData &renderData) {


   PhysicalObject::draw(renderData);


}


#define COLLISION_CLASS_NAME Checkpoint
#include "CollisionsBoilerplateCpp.h"
