#include "Corona.h"
#include "Magus.h"
#include "Player.h"
#include "Scene.h"
#include "Scenery.h"

const std::string Scenery::CLASS_NAME = "Scenery";

Scenery::Scenery(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
   : PhysicalObject(scene, model, name) {
}

Scenery::~Scenery() {
}

Json::Value Scenery::serialize() const {
   Json::Value root = PhysicalObject::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

void Scenery::tick(const float dt) {
    //Do nothing, it's just scenery
}

void Scenery::collideWith(PhysicalObject &other) {
   other.collideWith(*this);
}

void Scenery::collideWith(Scenery &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(*this, other);
   }
}

void Scenery::collideWith(Player &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(*this, other);
   }
}

void Scenery::collideWith(Magus &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(*this, other);
   }
}

void Scenery::collideWith(Corona &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(*this, other);
   }
}
