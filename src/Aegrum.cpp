//
//  Aegrum.cpp
//  Restoration
//
//  Created by Nathan Farnum on 5/11/14.
//  Copyright (c) 2014 Restoration Team. All rights reserved.
//

#include "Aegrum.h"

const std::string Aegrum::CLASS_NAME = "Aegrum";

const int Aegrum::ATTACK_POWER = 2;

//Put health in the creation of Magus, and damage
Aegrum::Aegrum(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: Vis(scene, model, ATTACK_POWER, name) {
}

Aegrum::~Aegrum() {
}

Json::Value Aegrum::serialize() const {
    Json::Value root = Vis::serialize();

    root["@class"] = CLASS_NAME;

    return root;
}

/*void Aegrum::tick(const float dt) {

}*/

void Aegrum::collideWith(PhysicalObject &other) {
    other.collideWith(*this);
}