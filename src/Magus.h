//
//  Magus.h
//  Restoration
//
//  Created by Nathan Farnum on 5/10/14.
//  Copyright (c) 2014 Restoration Team. All rights reserved.
//

#ifndef MAGUS_H
#define MAGUS_H

#include "Enemy.h"

class Magus : public Enemy {
protected:
   static const int BASE_HEALTH;
   static const float HOVER_SPEED;
   static const int ATTACK_POWER;
   float ATTACK_TIME;

public:    
   static const std::string CLASS_NAME;

   Magus(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
   virtual ~Magus();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   virtual void tick(const float dt);

   virtual int getAttackPower();

   virtual void reverseMovement();

   virtual void evasiveManuevers(glm::vec3 change);

#include "CollisionsBoilerplateH.h"
};

#endif /* defined(MAGUS_H) */
