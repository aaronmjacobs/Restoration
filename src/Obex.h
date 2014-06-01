#ifndef OBEX_H
#define OBEX_H

#include "Enemy.h"

class Obex : public Enemy {
protected:
   static const float BASE_HEALTH;
   static const float WALK_SPEED;
   static const float JUMP_FORCE;
   static const float ATTACK_POWER;
   static const float HEALTH_REPLACEMENT;
   static float ATTACK_TIME;
   static glm::vec3 SAVED_VELOCITY;
   static bool STOPPED;

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

   virtual float getAttackTime();

   virtual void resetAttackTime();

   virtual void setSavedVel(glm::vec3 svel);

   virtual bool getStoppedStatus();

   virtual void setStoppedStatus(bool status);

#include "CollisionsBoilerplateH.h"
};

#endif
