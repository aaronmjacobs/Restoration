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

class Corona : public Enemy {
protected:
    static const int BASE_HEALTH;
    static const float WALK_SPEED;
    static const float JUMP_FORCE;
    static const int ATTACK_POWER;
    
    bool wantsToGoLeft, wantsToGoRight, wantsToJump, wantsToAttack;
    
public:
    Corona(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
    ~Corona();
    
    virtual void tick(const float dt);
    virtual int getAttackPower();
};

#endif /* defined(MAGUS_H) */


