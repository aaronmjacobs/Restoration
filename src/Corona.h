//
//  Corona.h
//  Restoration
//
//  Created by Nathan Farnum on 5/10/14.
//  Copyright (c) 2014 Restoration Team. All rights reserved.
//

#ifndef CORONA_H
#define CORONA_H

#include "Enemy.h"

enum CoronaState { PATROLING, CHASING };

class Corona : public Enemy {
protected:
   static const float BASE_HEALTH;
   static const float WALK_SPEED;
   static const float JUMP_FORCE;
   static const float ATTACK_POWER;
   static const float HEALTH_REPLENISHMENT;
   static const float MAX_CHASE_DISTANCE;
   static const float MIN_CHASE_DISTANCE;

   CoronaState state;

public:
   static const std::string CLASS_NAME;

   Corona(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
   virtual ~Corona();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   virtual void tick(const float dt);

   virtual int getAttackPower();

   virtual void reverseMovement();

#include "CollisionsBoilerplateH.h"
};

#endif /* defined(CORONA_H) */
