//
//  Magus.cpp
//  Restoration
//
//  Created by Nathan Farnum on 5/10/14.
//  Copyright (c) 2014 Restoration Team. All rights reserved.
//

#include "GLIncludes.h"
#include "Loader.h"
#include "SceneGraph.h"

#include "CollisionsIncludes.h"
#include "Particle.h"

const std::string Magus::CLASS_NAME = "Magus";

const float Magus::BASE_HEALTH = 50.0f;
const float Magus::HOVER_SPEED = 4.0f;
const float Magus::HEALTH_REPLACEMENT = 10.0f;
const float Magus::ATTACK_POWER = 15.0f;

//Put health in the creation of Magus, and damage
Magus::Magus(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: Enemy(scene, model, BASE_HEALTH, HEALTH_REPLACEMENT, ATTACK_POWER, name) {
   attackTime = 5.0f;
}

Magus::~Magus() {
}

Json::Value Magus::serialize() const {
   Json::Value root = Enemy::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

void Magus::tick(const float dt) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      SPtr<Player> player = sScene->getPlayer().lock();
      if (player) {
         glm::vec3 playerPos = player->getPosition();
         glm::vec3 shootVec = glm::normalize(playerPos - position);
         
         if (glm::length(position - playerPos) < 30.0f) {
            if (attackTime < 2 && attackTime > 0) {
               //Chase a bit
               glm::vec3 chaseVec = glm::normalize(playerPos - position);
               setVelocity(chaseVec + chaseVec + chaseVec + chaseVec);
            } else if(attackTime > 0) {
               //Continue attacking
            } else {
               attackTime = 5.0f;

               float aegrumCreationDistance = 0.5f;
               float aegrumSpeed = 7.0f;
               glm::vec3 aegrumPos = position + shootVec * aegrumCreationDistance;

               Loader &loader = Loader::getInstance();
               Json::Value modelValue;
               modelValue["@class"] = "Model";
               modelValue["material"] = "aegrum";
               Json::Value meshValue;
               meshValue["@class"] = "Mesh";
               meshValue["fileName"] = "data/meshes/vis.obj";
               modelValue["mesh"] = meshValue;
               SPtr<Model> aegrumModel = loader.loadModel(sScene, modelValue);

               SPtr<Aegrum> aegrum = std::make_shared<Aegrum>(sScene, aegrumModel, ATTACK_POWER);
               aegrum->setRenderState(LIGHTWORLD_STATE | DARKWORLD_STATE);
               aegrum->setPosition(aegrumPos);
               aegrum->setVelocity(shootVec * aegrumSpeed + velocity);
               sScene->getSceneGraph()->addPhys(aegrum);

               glm::vec3 nVel = glm::normalize(aegrum->getVelocity());
               float angle = glm::acos(glm::dot(nVel, glm::vec3(1.0f, 0.0f, 0.0f)));
               if (nVel.y < 0) {
                  angle *= -1.0f;
               }
               aegrum->setOrientation(glm::angleAxis(angle, glm::vec3(0.0f, 0.0f, 1.0f)));
               sScene->getSceneGraph()->addPhys(aegrum);

               //Move around
               evasiveManuevers(playerPos - position);

               if (sScene) {
                  Particle::createEffect(sScene,
                                         getPosition(), // Position
                                         glm::vec3(0.0f),   // Velocity
                                         false,             // Gravity enabled
                                         5.0f,              // Size
                                         5,                // Number of particles
                                         3.0f,              // Duration (seconds)
                                         25.0f,             // Particle spread
                                         false);             // Stencil mode
               }

            }
            attackTime -= dt;
         }
      }
   }

    
   Enemy::tick(dt);
}

int Magus::getAttackPower() {
    return ATTACK_POWER;
}

void Magus::reverseMovement() {
   velocity.x *= -1.0f;
   velocity.y *= -1.0f;
}

void Magus::evasiveManuevers(glm::vec3 change) {
   float newX = change.y;
   float newY = change.x;

   velocity.x = newX;
   if (newY < 0)
      newY *= -1.0f;
   velocity.y = newY;
}

#define COLLISION_CLASS_NAME Magus
#include "CollisionsBoilerplateCpp.h"
