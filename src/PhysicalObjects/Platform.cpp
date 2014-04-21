#include "Platform.h"
#include "Player.h"
#include "../engine/Scene.h"

const std::string Platform::CLASS_NAME = "Platform";

std::list<Platform*> Platform::allPlatforms;

Platform::Platform(Scene *scene, const std::string &jsonFileName, const std::string &name, ModelRef model)
   : PhysicalObject(scene, jsonFileName, name, model) {
   allPlatforms.push_back(this);
}

Platform::~Platform() {
   allPlatforms.remove(this);
}

Json::Value Platform::serialize() const {
   Json::Value root = SceneNode::serialize();

   // Class name
   root["@class"] = CLASS_NAME;

   // AABB
   Json::Value boundsVal;
   boundsVal["xMin"] = boundingBox.xMin;
   boundsVal["xMax"] = boundingBox.xMax;
   boundsVal["yMin"] = boundingBox.yMin;
   boundsVal["yMax"] = boundingBox.yMax;
   root["bounds"] = boundsVal;

   return root;
}

void Platform::tick(const float dt) {
   // TODO
}

void Platform::move(glm::vec3 dir) {
   // TODO
}

void Platform::collideWith(PhysicalObject *physObj) {
   // Resolve the type of physObj through a polymorphic function call
   physObj->collideWith(this);
}

void Platform::collideWith(Player *player) {
   // We know the types of both colliding parties, tell the collision handler

   // Figure out when to use * vs Ref
   scene->getCollisionHanlder()->handleCollision(player, this); // TODO
}

void Platform::collideWith(Platform *platform) {
   // Do nothing for now
}
