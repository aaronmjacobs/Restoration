#ifndef VAGUS_H
#define VAGUS_H

#include "Enemy.h"

class Vagus : public Enemy {
protected:
   static const float BASE_HEALTH;
   static const float WALK_SPEED;
   static const float JUMP_FORCE;
   static const float HEALTH_REPLACEMENT;
   static const float ATTACK_POWER;
   float chaseTime;

public:
   static const std::string CLASS_NAME;

   Vagus(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
   virtual ~Vagus();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   virtual void tick(const float dt);

   virtual int getAttackPower();

   virtual void reverseMovement();

#include "CollisionsBoilerplateH.h"
};

#endif
