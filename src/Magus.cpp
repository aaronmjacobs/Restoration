//
//  Magus.cpp
//  Restoration
//
//  Created by Nathan Farnum on 5/10/14.
//  Copyright (c) 2014 Restoration Team. All rights reserved.
//

#include "GLIncludes.h"
#include "Magus.h"

const std::string Magus::CLASS_NAME = "Magus";

const int Magus::BASE_HEALTH = 7;
const float Magus::WALK_SPEED = 4.0f;
const float Magus::JUMP_FORCE = 300.0f;
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
    if (wantsToGoLeft) {
        position += glm::vec3(-WALK_SPEED * dt, 0.0f, 0.0f);
    }
    if (wantsToGoRight) {
        position += glm::vec3(WALK_SPEED * dt, 0.0f, 0.0f);
    }
    
    if (wantsToJump && onGround) {
        onGround = false;
        velocity += glm::vec3(0.0f, JUMP_FORCE, 0.0f) * dt;
    }
    
    if (wantsToAttack) {
        // TODO Handle attack logic
    }
    
    position += velocity * dt + 0.5f * acceleration * dt * dt;
    velocity += acceleration * dt;
}

int Magus::getAttackPower() {
    return ATTACK_POWER;
}
void Magus::collideWith(PhysicalObject &other) {
   other.collideWith(*this);
}
