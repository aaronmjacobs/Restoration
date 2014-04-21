#include "Platform.h"
#include "Player.h"
#include "../engine/Scene.h"

std::list<Platform*> Platform::allPlatforms;

Platform::Platform(Scene *scene, const std::string &jsonFileName, const std::string &name, ModelRef model)
   : PhysicalObject(scene, jsonFileName, name, model) {
   allPlatforms.push_back(this);
}

Platform::~Platform() {
   allPlatforms.remove(this);
}

void Platform::collideWith(Player *player) {
   // Figure out when to use * vs Ref
   scene->getCollisionHanlder()->handleCollision(player, this); // TODO
}
