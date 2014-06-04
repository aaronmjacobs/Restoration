#ifndef OBEX_H
#define OBEX_H

#include "Enemy.h"

enum ObexState { MOVING, STOPPED };

class Obex : public Enemy {
protected:
   static const float BASE_HEALTH;
   static const float WALK_SPEED;
   static const float ATTACK_POWER;
   static const float HEALTH_REPLACEMENT;
   static const float WAIT_TIME;

   ObexState state;
   float lastCollision;
   glm::vec3 moveVel;

public:
   static const std::string CLASS_NAME;

   Obex(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
   virtual ~Obex();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   virtual void draw(const RenderData &renderData);

   virtual void tick(const float dt);

   virtual int getAttackPower();

   virtual void reverseMovement();

#include "CollisionsBoilerplateH.h"
};

#endif
