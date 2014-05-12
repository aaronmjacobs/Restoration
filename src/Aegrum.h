//
//  Aegrum.h
//  Restoration
//
//  Created by Nathan Farnum on 5/11/14.
//  Copyright (c) 2014 Restoration Team. All rights reserved.
//

//Magus's Vis

#ifndef AEGRUM_H
#define AEGRUM_H

#include "Vis.h"

class Aegrum : public Vis {
protected:
    static const int ATTACK_POWER;

public:
    static const std::string CLASS_NAME;

    Aegrum(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
    virtual ~Aegrum();

    /**
     * Serializes the object to JSON.
     */
    virtual Json::Value serialize() const;

    //virtual void tick(const float dt);

    virtual void collideWith(PhysicalObject &other);
};

#endif /* defined(AEGRUM_H) */
