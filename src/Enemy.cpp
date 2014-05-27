//
//  Enemy.cpp
//  Restoration
//
//  Created by Nathan Farnum on 5/10/14.
//  Copyright (c) 2014 Restoration Team. All rights reserved.
//

#include "GLIncludes.h"

#include "CollisionsIncludes.h"

const std::string Enemy::CLASS_NAME = "Enemy";

int Enemy::numEnemies = 0;
int Enemy::maxEnemies = 0;

Enemy::Enemy(SPtr<Scene> scene, SPtr<Model> model, int health, int attackPower, const std::string &name)
: Character(scene, model, health, name) {
   ++numEnemies;
   ++maxEnemies;
}

Enemy::~Enemy() {
   --numEnemies;
}

Json::Value Enemy::serialize() const {
   Json::Value root = Character::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}
