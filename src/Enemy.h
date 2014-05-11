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
#include "InputListener.h"

class Enemy : public Character, public InputListener {
public:
    Enemy(SPtr<Scene> scene, SPtr<Model> model, int health, const std::string &name = "");
    
    virtual ~Enemy();
};
#endif /* defined(ENEMY_H) */


