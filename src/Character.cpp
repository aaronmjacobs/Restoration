#include "CollisionsIncludes.h"

const std::string Character::CLASS_NAME = "Character";

Character::Character(SPtr<Scene> scene, SPtr<Model> model, int health, const std::string &name)
   : MovableObject(scene, model, name), health(health), onGround(false) {
}

Character::~Character() {
}

Json::Value Character::serialize() const {
   Json::Value root = MovableObject::serialize();

   root["@class"] = CLASS_NAME;

   // Health
   root["health"] = health;

   return root;
}

void Character::draw(const RenderData &renderData) {
   glm::vec3 front = glm::normalize(getVelocity());
   if (glm::length(front) > 0.0001f) {
      glm::vec3 rest(0.0f, 0.0f, 1.0f);
      float angle = glm::acos(glm::dot(front, rest));
      if (front.x < 0.0f) {
         angle *= -1.0f;
      }

      setOrientation(glm::angleAxis(angle, glm::vec3(0.0f, 1.0f, 0.0f)));
   }

   MovableObject::draw(renderData);
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
