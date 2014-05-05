#include "CollisionHandler.h"
#include "MovableObject.h"
#include "Scene.h"

CollisionHandler::CollisionHandler(Scene &scene)
   : scene(scene) {
}

CollisionHandler::~CollisionHandler() {
}

void CollisionHandler::handleCollision(MovableObject &first, MovableObject &second) {
   std::cout << "Colliding" << std::endl;
}