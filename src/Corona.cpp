//
//  Corona.cpp
//  Restoration
//
//  Created by Nathan Farnum on 5/10/14.
//  Copyright (c) 2014 Restoration Team. All rights reserved.
//

#include "Corona.h"
#include "GLIncludes.h"
#include "Magus.h"
#include "Player.h"
#include "Scene.h"

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
    
    if (!isAlive()) {
        markForRemoval();
    }
}

int Corona::getAttackPower() {
    return ATTACK_POWER;
}

void Corona::reverseMovement() {
    if (wantsToGoLeft) {
        wantsToGoLeft = false;
        wantsToGoRight = true;
    } else {
        wantsToGoLeft = true;
        wantsToGoRight = false;
    }
}

void Corona::platformReaction() {
    if(!onGround) {
        //////fiiiiinnnniiisssshhhhh
    }
}

void Corona::collideWith(PhysicalObject &other) {
   other.collideWith(*this);
}

void Corona::collideWith(Scenery &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(*this, other);
   }
}

void Corona::collideWith(Player &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(*this, other);
   }
}

void Corona::collideWith(Magus &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(*this, other);
   }
}

void Corona::collideWith(Corona &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(*this, other);
   }
}

