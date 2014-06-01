#include "GLIncludes.h"

#include "CollisionsIncludes.h"

const std::string Vagus::CLASS_NAME = "Vagus";

const float Vagus::BASE_HEALTH = 20.0f;
const float Vagus::WALK_SPEED = 3.0f;
const float Vagus::JUMP_FORCE = 300.0f;
const float Vagus::HEALTH_REPLACEMENT = 3.0f;
const float Vagus::ATTACK_POWER = 10.0f;

Vagus::Vagus(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: Enemy(scene, model, BASE_HEALTH, HEALTH_REPLACEMENT, ATTACK_POWER, name) {
}

Vagus::~Vagus() {
}

Json::Value Vagus::serialize() const {
   Json::Value root = Enemy::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

void Vagus::tick(const float dt) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      SPtr<Player> player = sScene->getPlayer().lock();
      if (player) {
         glm::vec3 playerPos = player->getPosition();
       
         glm::vec3 chaseVec = glm::normalize(playerPos - position);
         if (glm::length(position - playerPos) < 10.0f) {
            setVelocity(chaseVec * WALK_SPEED);
         }
      }
   }

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
