#include "GLIncludes.h"

#include "CollisionsIncludes.h"

const std::string Obex::CLASS_NAME = "Obex";

const float Obex::BASE_HEALTH = 20.0f;
const float Obex::WALK_SPEED = 10.0f;
const float Obex::HEALTH_REPLACEMENT = 3.0f;
const float Obex::ATTACK_POWER = 15.0f;
const float Obex::WAIT_TIME = 1.0f;

Obex::Obex(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: Enemy(scene, model, BASE_HEALTH, HEALTH_REPLACEMENT, ATTACK_POWER, name) {
   state = MOVING;
   lastCollision = 0.0f;
   moveVel = glm::vec3(WALK_SPEED, 0.0f, 0.0f);
}

Obex::~Obex() {
}

Json::Value Obex::serialize() const {
   Json::Value root = Enemy::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

void Obex::draw(const RenderData &renderData) {
   // Skip the character draw, so the orientation doesn't change
   MovableObject::draw(renderData);
}

void Obex::tick(const float dt) {
   if (state == STOPPED) {
      velocity = glm::vec3(0.0f);
      lastCollision += dt;

      if (lastCollision > WAIT_TIME) {
         state = MOVING;
         moveVel.x *= -1.0f;
         lastCollision = 0.0f;
      }
   }

   if (state == MOVING) {
      velocity = moveVel;
   }

   Enemy::tick(dt);
}

int Obex::getAttackPower() {
   return ATTACK_POWER;
}

void Obex::reverseMovement() {
   state = STOPPED;
}

#define COLLISION_CLASS_NAME Obex
#include "CollisionsBoilerplateCpp.h"
