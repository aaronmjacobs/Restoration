#include "Character.h"

Character::Character(SPtr<Scene> scene, SPtr<Model> model, int health, const std::string &name)
   : MovableObject(scene, model, name), health(health), onGround(false) {
}

Character::~Character() {
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
