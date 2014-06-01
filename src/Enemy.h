//
//  Enemy.h
//  Restoration
//
//  Created by Nathan Farnum on 5/10/14.
//  Copyright (c) 2014 Restoration Team. All rights reserved.
//

#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character {
public:
   static const std::string CLASS_NAME;
   const float damage;
   const float healthReplenishment;

   Enemy(SPtr<Scene> scene, SPtr<Model> model, float health, float healthReplenishment, float damage, const std::string &name = "");
    
   virtual ~Enemy();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;
    
   virtual void reverseMovement() = 0;

   virtual int getAttackPower() = 0;

   float getHealthReplenishment();
   float getDamage();
};

#endif /* defined(ENEMY_H) */
