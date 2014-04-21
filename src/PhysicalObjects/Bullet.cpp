#include "Bullet.h"
#include "Enemy.h"

Bullet::Bullet(Scene *scene, const std::string &jsonFileName, const std::string &name, ModelRef model, glm::vec3 dir)
   : PhysicalObject(scene, jsonFileName, name, model) {
   velocity = dir;
}

void Bullet::move(glm::vec3 dir) {
   // TODO
   translateBy(dir);
}

void Bullet::tick(const float dt) {
   move(velocity * dt);

   // Enemies
   for (Enemy *enemy : Enemy::allEnemies) {
      if (checkCollision(enemy)) {
         scene->getCollisionHanlder()->handleCollision(enemy, this); // TODO
      }
   }
}

void Bullet::die() {
   alive = false;
   translateBy(glm::vec3(0.0f, -500.0f, 500.0f));
}
