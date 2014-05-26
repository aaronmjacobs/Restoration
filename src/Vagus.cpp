#include "GLIncludes.h"

#include "CollisionsIncludes.h"

const std::string Vagus::CLASS_NAME = "Vagus";

const int Vagus::BASE_HEALTH = 14;
const float Vagus::WALK_SPEED = 2.0f;
const float Vagus::JUMP_FORCE = 300.0f;
const int Vagus::ATTACK_POWER = 4;

Vagus::Vagus(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: Enemy(scene, model, BASE_HEALTH, ATTACK_POWER, name) {
}

Vagus::~Vagus() {
}

Json::Value Vagus::serialize() const {
   Json::Value root = Enemy::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

void Vagus::tick(const float dt) {
   // TODO AI

   Enemy::tick(dt);
}

int Vagus::getAttackPower() {
   return ATTACK_POWER;
}

void Vagus::reverseMovement() {
   velocity.x *= -1.0f;
}

#define COLLISION_CLASS_NAME Vagus
#include "CollisionsBoilerplateCpp.h"
