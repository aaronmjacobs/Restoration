#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"

class Boss : public Enemy {
protected:
   static const float BASE_HEALTH;
   static const float HOVER_SPEED;
   static const float ATTACK_POWER;
   static const float HEALTH_REPLACEMENT;
   static float ATTACK_TIME;

public:
   static const std::string CLASS_NAME;

   Boss(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
   virtual ~Boss();

   /**
   * Serializes the object to JSON.
   */
   virtual Json::Value serialize() const;

   virtual void tick(const float dt);

   virtual int getAttackPower();

#include "CollisionsBoilerplateH.h"
};

#endif /* defined(BOSS_H) */