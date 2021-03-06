#ifndef CHARACTER_H
#define CHARACTER_H

#include "MovableObject.h"

class Character : public MovableObject {
protected:
   float health;
   bool onGround;

public:
   static const std::string CLASS_NAME;

   Character(SPtr<Scene> scene, SPtr<Model> model, float health, const std::string &name = "");
   virtual ~Character();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   virtual void draw(const RenderData &renderData);

   virtual void tick(const float dt);

   float getHealth();
   bool isOnGround();
   bool isAlive();
   void setHealth(float health);
   void setOnGround();
};

#endif
