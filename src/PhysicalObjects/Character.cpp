#include "Character.h"

Character::Character(Scene *scene, const std::string &jsonFileName, const std::string &name, ModelRef model)
: PhysicalObject(scene, jsonFileName, name, model) {
}

Character::~Character() {
}

int Character::getHealth(){
   return this->health;
}

void Character::loseHealth(int harm){
   this->health -= harm;
}

void Character::regenHealth(int heal){
   this->health += heal;
}