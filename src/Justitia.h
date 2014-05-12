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
#include "Aegrum.h"

class Justitia : public Vis {
protected:
    static const int ATTACK_POWER;
   const double LIFE_SECONDS = 2.0;
   double startTime;

public:
    static const std::string CLASS_NAME;

    Justitia(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
    virtual ~Justitia();

    /**
     * Serializes the object to JSON.
     */
    virtual Json::Value serialize() const;

   /**
    * Draws the geometry in the scene.
    */
   virtual void draw(unsigned int renderState);

    virtual void tick(const float dt);

   virtual void collideWith(PhysicalObject &other);
   virtual void collideWith(Scenery &other);
   virtual void collideWith(Player &other);
   virtual void collideWith(Magus &other);
   virtual void collideWith(Corona &other);
   virtual void collideWith(Justitia &other);
   virtual void collideWith(Aegrum &other);
};

#endif /* defined(JUSTITIA_H) */
