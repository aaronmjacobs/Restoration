//
//  Justitia.h
//  Restoration
//
//  Created by Nathan Farnum on 5/11/14.
//  Copyright (c) 2014 Restoration Team. All rights reserved.
//

//Player's Vis

#ifndef JUSTITIA_H
#define JUSTITIA_H

#include "Vis.h"

class Justitia : public Vis {
protected:
    static const int ATTACK_POWER;

public:
    static const std::string CLASS_NAME;

    Justitia(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
    virtual ~Justitia();

    /**
     * Serializes the object to JSON.
     */
    virtual Json::Value serialize() const;

    //virtual void tick(const float dt);

    virtual void collideWith(PhysicalObject &other);
};

#endif /* defined(JUSTITIA_H) */
