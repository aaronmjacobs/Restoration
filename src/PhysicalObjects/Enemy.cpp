#include "Enemy.h"

Enemy::Enemy(const std::string &jsonFileName, const std::string &name, ModelRef model)
: Character(jsonFileName, name, model) {
}

Enemy::~Enemy() {
}