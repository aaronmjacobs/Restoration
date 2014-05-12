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

const int Magus::BASE_HEALTH = 8;
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
    if (wantsToGoLeft) {
        position += glm::vec3(-HOVER_SPEED * dt, 0.0f, 0.0f);
    }
    if (wantsToGoRight) {
        position += glm::vec3(HOVER_SPEED * dt, 0.0f, 0.0f);
    }
    
    if (wantsToGoUp) {
        position += glm::vec3(0.0f, HOVER_SPEED * dt, 0.0f);
    }
    
    if (wantsToGoDown && !onGround) {
        position += glm::vec3(0.0f, -HOVER_SPEED * dt, 0.0f);
    }
    
    if (wantsToAttack) {
        // TODO Handle attack logic
    }
    
    position += velocity * dt + 0.5f * acceleration * dt * dt;
    velocity += acceleration * dt;
    
    if (getHealth() <= 0) {
        markForRemoval();
    }
}

int Magus::getAttackPower() {
    return ATTACK_POWER;
}
void Magus::collideWith(PhysicalObject &other) {
   other.collideWith(*this);
}

void Magus::reverseMovement() {
    if (wantsToGoLeft) {
        wantsToGoLeft = false;
        wantsToGoRight = true;
    } else {
        wantsToGoLeft = true;
        wantsToGoRight = false;
    }
    if (wantsToGoUp) {
        wantsToGoUp = false;
        wantsToGoDown = true;
    } else {
        wantsToGoUp = true;
        wantsToGoDown = false;
    }
}
