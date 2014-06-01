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

Enemy::Enemy(SPtr<Scene> scene, SPtr<Model> model, float health, float healthReplenishment, float damage, const std::string &name)
: Character(scene, model, health, name), healthReplenishment(healthReplenishment), damage(damage) {
}

Enemy::~Enemy() {
}

Json::Value Enemy::serialize() const {
   Json::Value root = Character::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

float Enemy::getHealthReplenishment() {
   return healthReplenishment;
}

float Enemy::getDamage() {
   return damage;
}
