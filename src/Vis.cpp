//
//  Vis.cpp
//  Restoration
//
//  Created by Nathan Farnum on 5/11/14.
//  Copyright (c) 2014 Restoration Team. All rights reserved.
//

#include "Vis.h"

const std::string MovableObject::CLASS_NAME = "Vis";

Vis::Vis(SPtr<Scene> scene, SPtr<Model> model, int attackPower, const std::string &name)
: MovableObject(scene, model, name),  attackPower(attackPower){
}

Vis::~Vis() {
}

Json::Value Vis::serialize() const {
    Json::Value root = MovableObject::serialize();

    root["@class"] = CLASS_NAME;

    //root["attackPower"] = attackPower;

    return root;
}

void Vis::removeVis() {
    markForRemoval();
}

int Vis::getAttackPower() {
    return attackPower;
}

//Set velocity when attacking with Player. Direction is based on velocity
void Vis::tick(const float dt) {
    position += velocity;
}