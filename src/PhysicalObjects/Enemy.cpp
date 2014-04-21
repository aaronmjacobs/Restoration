#include "Enemy.h"
#include "Platform.h"

Enemy::Enemy(Scene *scene, const std::string &jsonFileName, const std::string &name, ModelRef model)
: Character(scene, jsonFileName, name, model) {
   acceleration = glm::vec3(0.0f, -9.8f, 0.0f);
   velocity = glm::vec3(5.0f, 0.0f, 0.0f);
}

Enemy::~Enemy() {
}

void Enemy::tick(const float dt) {
   velocity += acceleration * dt;
   move(velocity * dt);

   // Platforms
   for (Platform *platform : Platform::allPlatforms) {
      if (checkCollision(platform)) {
         scene->getCollisionHanlder()->handleCollision(this, platform); // TODO
      }
   }
}

void Enemy::move(glm::vec3 dir) {
   // TODO
   translateBy(dir);
}

void Enemy::attack() {

}
