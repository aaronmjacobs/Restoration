//
//  Corona.cpp
//  Restoration
//
//  Created by Nathan Farnum on 5/10/14.
//  Copyright (c) 2014 Restoration Team. All rights reserved.
//

#include "Corona.h"

#include "GLIncludes.h"
#include "Enemy.h"

const int Corona::BASE_HEALTH = 14;
const float Corona::WALK_SPEED = 2.0f;
const float Corona::JUMP_FORCE = 300.0f;

Corona::Corona(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: Enemy(scene, model, BASE_HEALTH, name) {
}

Corona::~Corona() {
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
}
