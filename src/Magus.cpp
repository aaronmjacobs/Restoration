//
//  Magus.cpp
//  Restoration
//
//  Created by Nathan Farnum on 5/10/14.
//  Copyright (c) 2014 Restoration Team. All rights reserved.
//

#include "GLIncludes.h"

#include "CollisionsIncludes.h"

const std::string Magus::CLASS_NAME = "Magus";

const int Magus::BASE_HEALTH = 7;
const float Magus::HOVER_SPEED = 4.0f;
const int Magus::ATTACK_POWER = 1;

//Put health in the creation of Magus, and damage
Magus::Magus(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: Enemy(scene, model, BASE_HEALTH, ATTACK_POWER, name) {
}

Magus::~Magus() {
}

Json::Value Magus::serialize() const {
   Json::Value root = Enemy::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

void Magus::tick(const float dt) {
   // TODO AI
    
   Enemy::tick(dt);
}

int Magus::getAttackPower() {
    return ATTACK_POWER;
}

void Magus::reverseMovement() {
   velocity.x *= -1.0f;
}

#define COLLISION_CLASS_NAME Magus
#include "CollisionsBoilerplateCpp.h"
