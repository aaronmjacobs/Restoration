#ifndef BULLET_H
#define BULLET_H

#include "PhysicalObject.h"

class Bullet;
typedef std::shared_ptr<Bullet> BulletRef;

class Bullet : public PhysicalObject {
public:
   bool alive;
   glm::vec3 velocity;

   Bullet(Scene *scene, const std::string &jsonFileName, const std::string &name, ModelRef model, glm::vec3 dir);
   virtual void move(glm::vec3 dir);
   virtual void tick(const float dt);
   void die();
};

#endif
