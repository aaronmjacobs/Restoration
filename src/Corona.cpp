//
//  Corona.cpp
//  Restoration
//
//  Created by Nathan Farnum on 5/10/14.
//  Copyright (c) 2014 Restoration Team. All rights reserved.
//

#include "GLIncludes.h"

#include "CollisionsIncludes.h"

const std::string Corona::CLASS_NAME = "Corona";

const int Corona::BASE_HEALTH = 14;
const float Corona::WALK_SPEED = 2.0f;
const float Corona::JUMP_FORCE = 300.0f;
const int Corona::ATTACK_POWER = 4;

Corona::Corona(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: Enemy(scene, model, BASE_HEALTH, ATTACK_POWER, name) {
}

Corona::~Corona() {
}

Json::Value Corona::serialize() const {
   Json::Value root = Enemy::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

void Corona::tick(const float dt) {
   // TODO AI

   Enemy::tick(dt);
}

int Corona::getAttackPower() {
    return ATTACK_POWER;
}

void Corona::reverseMovement() {
   velocity.x *= -1.0f;
}

void Corona::platformReaction() {
    if(!onGround) {
        //////fiiiiinnnniiisssshhhhh
    }
}

#define COLLISION_CLASS_NAME Corona
#include "CollisionsBoilerplateCpp.h"



