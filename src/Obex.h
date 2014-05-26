#ifndef OBEX_H
#define OBEX_H

#include "Enemy.h"

class Obex : public Enemy {
protected:
   static const int BASE_HEALTH;
   static const float WALK_SPEED;
   static const float JUMP_FORCE;
   static const int ATTACK_POWER;

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