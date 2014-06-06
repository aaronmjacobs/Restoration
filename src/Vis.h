#ifndef VIS_H
#define VIS_H

#include "MovableObject.h"

class Vis : public MovableObject {
protected:
   const float LIFE_SECONDS = 2.0f;
   float attackPower;
   float lifeTime;

public:
   static const std::string CLASS_NAME;

   Vis(SPtr<Scene> scene, SPtr<Model> model, const float attackPower, const std::string &name = "");

   virtual ~Vis();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   virtual bool shouldBeSerialized() {
      return false;
   }

   float getAttackPower();
   void setAttackPower(float attackPower);
};

#endif
