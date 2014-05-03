#ifndef CHARACTER_H
#define CHARACTER_H

#include "MovableObject.h"

class Character : public MovableObject {
protected:
   int health;
   bool onGround;

public:
   Character(SPtr<Scene> scene, SPtr<Model> model, int health, const std::string &name = "");
   virtual ~Character();

   int getHealth();
   bool isOnGround();
   bool isAlive();
   void setHealth(int health);
   void setOnGround();
};

#endif
