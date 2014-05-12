//
//  Justitia.cpp
//  Restoration
//
//  Created by Nathan Farnum on 5/11/14.
//  Copyright (c) 2014 Restoration Team. All rights reserved.
//

#include "Justitia.h"
#include "Scene.h"
#include "Magus.h"
#include "Player.h"
#include "Corona.h"
#include "GLIncludes.h"

const std::string Justitia::CLASS_NAME = "Justitia";

const int Justitia::ATTACK_POWER = 2;

//Put health in the creation of Magus, and damage
Justitia::Justitia(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: Vis(scene, model, ATTACK_POWER, name) {
   startTime = glfwGetTime();
}

Justitia::~Justitia() {
}

Json::Value Justitia::serialize() const {
    Json::Value root = Vis::serialize();

    root["@class"] = CLASS_NAME;

    return root;
}

void Justitia::tick(const float dt) {
   if (glfwGetTime() - startTime > LIFE_SECONDS) {
      markForRemoval();
      return;
   }

   Vis::tick(dt);
}

void Justitia::draw(unsigned int renderState) {
   if (renderState == STENCIL_STATE) {
      scale = glm::vec3(4.0f);
   } else {
      scale = glm::vec3(1.25f);
   }

   Vis::draw(renderState);
}

void Justitia::collideWith(PhysicalObject &other) {
    other.collideWith(*this);
}

void Justitia::collideWith(Justitia &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(*this, other);
   }
}

void Justitia::collideWith(Aegrum &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(*this, other);
   }
}

void Justitia::collideWith(Scenery &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(*this, other);
   }
}

void Justitia::collideWith(Player &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(*this, other);
   }
}

void Justitia::collideWith(Magus &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(*this, other);
   }
}

void Justitia::collideWith(Corona &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(*this, other);
   }
}
