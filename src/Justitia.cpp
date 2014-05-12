//
//  Justitia.cpp
//  Restoration
//
//  Created by Nathan Farnum on 5/11/14.
//  Copyright (c) 2014 Restoration Team. All rights reserved.
//

#include "Justitia.h"

const std::string Justitia::CLASS_NAME = "Justitia";

const int Justitia::ATTACK_POWER = 2;

//Put health in the creation of Magus, and damage
Justitia::Justitia(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: Vis(scene, model, ATTACK_POWER, name) {
}

Justitia::~Justitia() {
}

Json::Value Justitia::serialize() const {
    Json::Value root = Vis::serialize();

    root["@class"] = CLASS_NAME;

    return root;
}

/*void Justitia::tick(const float dt) {

}*/

void Justitia::collideWith(PhysicalObject &other) {
    other.collideWith(*this);
}