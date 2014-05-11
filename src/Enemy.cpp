//
//  Enemy.cpp
//  Restoration
//
//  Created by Nathan Farnum on 5/10/14.
//  Copyright (c) 2014 Restoration Team. All rights reserved.
//

#include "GLIncludes.h"
#include "Enemy.h"



Enemy::Enemy(SPtr<Scene> scene, SPtr<Model> model, int health, const std::string &name)
: Character(scene, model, health, name) {
}

Enemy::~Enemy() {
}
