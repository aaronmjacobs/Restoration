#include "Enemy.h"

Enemy::Enemy(Scene *scene, const std::string &jsonFileName, const std::string &name, ModelRef model)
: Character(scene, jsonFileName, name, model) {
}

Enemy::~Enemy() {
}