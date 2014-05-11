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
    
    bool wantsToGoLeft, wantsToGoRight, wantsToJump, wantsToAttack;
    
public:
    Magus(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
    ~Magus();
    
    virtual void tick(const float dt);
};

#endif /* defined(MAGUS_H) */

