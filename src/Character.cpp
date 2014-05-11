#include "Character.h"

const std::string Character::CLASS_NAME = "Character";

Character::Character(SPtr<Scene> scene, SPtr<Model> model, int health, const std::string &name)
   : MovableObject(scene, model, name), health(health), onGround(false) {
}

Character::~Character() {
}

Json::Value Character::serialize() const {
   Json::Value root = MovableObject::serialize();

   root["@class"] = CLASS_NAME;

   // Health
   root["health"] = health;

   return root;
}

int Character::getHealth() {
   return health;
}

bool Character::isOnGround() {
   return onGround;
}

bool Character::isAlive() {
   return health > 0;
}

void Character::setHealth(int health) {
   this->health = health;
}

void Character::setOnGround() {
   onGround = true;
}
