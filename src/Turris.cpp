#include "GLIncludes.h"

#include "CollisionsIncludes.h"

const std::string Turris::CLASS_NAME = "Turris";

const int Turris::BASE_HEALTH = 14;
const int Turris::ATTACK_POWER = 4;

Turris::Turris(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: Enemy(scene, model, BASE_HEALTH, ATTACK_POWER, name) {
}

Turris::~Turris() {
}

Json::Value Turris::serialize() const {
   Json::Value root = Enemy::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

void Turris::tick(const float dt) {
   // TODO AI

   Enemy::tick(dt);
}

int Turris::getAttackPower() {
   return ATTACK_POWER;
}

#define COLLISION_CLASS_NAME Turris
#include "CollisionsBoilerplateCpp.h"
