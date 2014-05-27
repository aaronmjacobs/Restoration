#ifndef TURRIS_H
#define TURRIS_H

#include "Enemy.h"

class Turris : public Enemy {
protected:
   static const int BASE_HEALTH;
   static const int ATTACK_POWER;
   float ATTACK_TIME;

public:
   static const std::string CLASS_NAME;

   Turris(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
   virtual ~Turris();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   virtual void draw(const RenderData &renderData);

   virtual void tick(const float dt);

   virtual int getAttackPower();

   virtual void reverseMovement() {
   }

#include "CollisionsBoilerplateH.h"
};

#endif
