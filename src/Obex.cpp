#include "GLIncludes.h"

#include "CollisionsIncludes.h"

const std::string Obex::CLASS_NAME = "Obex";

const float Obex::BASE_HEALTH = 20.0f;
const float Obex::WALK_SPEED = 2.0f;
const float Obex::JUMP_FORCE = 300.0f;
const float Obex::HEALTH_REPLACEMENT = 3.0f;
const float Obex::ATTACK_POWER = 15.0f;

float Obex::ATTACK_TIME = 0.0f;
bool Obex::STOPPED = true;
glm::vec3 Obex::SAVED_VELOCITY = glm::vec3(0.0, 0.0, 0.0);

Obex::Obex(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: Enemy(scene, model, BASE_HEALTH, HEALTH_REPLACEMENT, ATTACK_POWER, name) {

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
   // TODO AI


   if(ATTACK_TIME <= 0.0f) {
      setStoppedStatus(false);
      velocity = SAVED_VELOCITY;
   } else if (STOPPED) {
      velocity = glm::vec3(0.0, 0.0, 0.0);
   }
   ATTACK_TIME -= dt;
  

   Enemy::tick(dt);

   /*printf("vel: %f\n", getVelocity().x);
   printf("svel: %f\n", SAVED_VELOCITY.x);

   if (ATTACK_TIME < 4.0f && getVelocity().x > 0.0f && getVelocity().y > 0.0f) {
      setSavedVel(getVelocity());

      printf("in1: %f\n", ATTACK_TIME);
      setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
   } else if (ATTACK_TIME >= 4.0f && getVelocity() != SAVED_VELOCITY) {
      printf("in2: %f\n", ATTACK_TIME);
      setVelocity(SAVED_VELOCITY);
      reverseMovement();
   }
   ATTACK_TIME += dt;
printf("vel2: %f\n\n", getVelocity().x);
   Enemy::tick(dt);*/
}

int Obex::getAttackPower() {
   return ATTACK_POWER;
}

void Obex::reverseMovement() {
   velocity.x *= -1.0f;
}

float Obex::getAttackTime() {
   return ATTACK_TIME;
}

void Obex::resetAttackTime() {
   ATTACK_TIME = 5.0;
}

void Obex::setSavedVel(glm::vec3 svel) {
   SAVED_VELOCITY = svel;
}

bool Obex::getStoppedStatus() {
   return STOPPED;
}

void Obex::setStoppedStatus(bool status) {
   STOPPED = status;
}

#define COLLISION_CLASS_NAME Obex
#include "CollisionsBoilerplateCpp.h"
