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

class Corona;
class Player;
class PhysicalObject;
class Scenery;

class Magus : public Enemy {
protected:
   static const int BASE_HEALTH;
   static const float HOVER_SPEED;
    static const int ATTACK_POWER;

   bool wantsToGoLeft, wantsToGoRight, wantsToGoUp, wantsToGoDown, wantsToAttack;

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

   virtual void collideWith(PhysicalObject &other);
   virtual void collideWith(Scenery &other);
   virtual void collideWith(Player &other);
   virtual void collideWith(Magus &other);
   virtual void collideWith(Corona &other);
};

#endif /* defined(MAGUS_H) */
