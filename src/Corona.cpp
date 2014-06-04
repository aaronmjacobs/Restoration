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

const float Corona::BASE_HEALTH = 30.0f;
const float Corona::WALK_SPEED = 3.0f;
const float Corona::JUMP_FORCE = 300.0f;
const float Corona::ATTACK_POWER = 7.0f;
const float Corona::HEALTH_REPLENISHMENT = 5.0f;
const float Corona::MAX_CHASE_DISTANCE = 10.0f;
const float Corona::MIN_CHASE_DISTANCE = 0.5f;

Corona::Corona(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: Enemy(scene, model, BASE_HEALTH, HEALTH_REPLENISHMENT, ATTACK_POWER, name) {
   state = PATROLING;
}

Corona::~Corona() {
}

Json::Value Corona::serialize() const {
   Json::Value root = Enemy::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

void Corona::tick(const float dt) {
   state = PATROLING;

   SPtr<Player> player;
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      player = sScene->getPlayer().lock();
      if (player) {
         float toPlayerLen = glm::abs(position.x - player->getPosition().x);
         if (toPlayerLen < MAX_CHASE_DISTANCE) {
            state = CHASING;
         }
      }
   }

   if (state == CHASING && player) {
      if (position.x < player->getPosition().x - MIN_CHASE_DISTANCE) {
         velocity.x = WALK_SPEED;
      } else if (position.x > player->getPosition().x + MIN_CHASE_DISTANCE) {
         velocity.x = -WALK_SPEED;
      } else {
         velocity.x = 0.0f;
      }
   } else { // state == PATROLING
      if (velocity.x == 0.0f) {
         velocity.x = WALK_SPEED;
      }
   }

   Enemy::tick(dt);
}

int Corona::getAttackPower() {
    return ATTACK_POWER;
}

void Corona::reverseMovement() {
   if (state == PATROLING) {
      velocity.x *= -1.0f;
   }
}

#define COLLISION_CLASS_NAME Corona
#include "CollisionsBoilerplateCpp.h"
