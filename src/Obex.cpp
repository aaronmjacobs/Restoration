#include "GLIncludes.h"

#include "CollisionsIncludes.h"

const std::string Obex::CLASS_NAME = "Obex";

const int Obex::BASE_HEALTH = 14;
const float Obex::WALK_SPEED = 2.0f;
const float Obex::JUMP_FORCE = 300.0f;
const int Obex::ATTACK_POWER = 4;

Obex::Obex(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: Enemy(scene, model, BASE_HEALTH, ATTACK_POWER, name) {
}

Obex::~Obex() {
}

Json::Value Obex::serialize() const {
   Json::Value root = Enemy::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

void Obex::tick(const float dt) {
   // TODO AI

   Enemy::tick(dt);
}

int Obex::getAttackPower() {
   return ATTACK_POWER;
}

void Obex::reverseMovement() {
   velocity.x *= -1.0f;
}

#define COLLISION_CLASS_NAME Obex
#include "CollisionsBoilerplateCpp.h"
