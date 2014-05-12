//
//  Vis.h
//  Restoration
//
//  Created by Nathan Farnum on 5/11/14.
//  Copyright (c) 2014 Restoration Team. All rights reserved.
//

//Energy shot

#ifndef VIS_H
#define VIS_H

#include "MovableObject.h"

class Vis : public MovableObject {
protected:
    int attackPower;

public:
    static const std::string CLASS_NAME;

    Vis(SPtr<Scene> scene, SPtr<Model> model, int attackPower, const std::string &name = "");

    virtual ~Vis();

    /**
     * Serializes the object to JSON.
     */
    virtual Json::Value serialize() const;

    void removeVis();

    int getAttackPower();

    virtual void tick(const float dt);
    
};




#endif /* defined(VIS_H) */