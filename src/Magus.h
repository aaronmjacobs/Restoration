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
   static const float WALK_SPEED;
   static const float JUMP_FORCE;
    static const int ATTACK_POWER;

   bool wantsToGoLeft, wantsToGoRight, wantsToJump, wantsToAttack;

   static const std::string CLASS_NAME;

   Magus(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
   virtual ~Magus();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   virtual void tick(const float dt);

   virtual void collideWith(PhysicalObject &other);
    
    virtual int getAttackPower();
};

#endif /* defined(MAGUS_H) */
