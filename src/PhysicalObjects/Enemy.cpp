#include "Enemy.h"
#include "Platform.h"

std::list<Enemy*> Enemy::allEnemies;

Enemy::Enemy(Scene *scene, const std::string &jsonFileName, const std::string &name, ModelRef model)
: Character(scene, jsonFileName, name, model) {
   acceleration = glm::vec3(0.0f, -9.8f, 0.0f);
   velocity = glm::vec3(5.0f, 0.0f, 0.0f);
   alive = true;

   allEnemies.push_back(this);
}

Enemy::~Enemy() {
   allEnemies.remove(this);
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

void Enemy::die() {
   alive = false;
   translateBy(glm::vec3(0.0f, -500.0f, 500.0f));
}

void Enemy::move(glm::vec3 dir) {
   // TODO
   translateBy(dir);
}

void Enemy::attack() {

}
