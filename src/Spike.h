#ifndef SPIKE_H
#define SPIKE_H

#include "Scenery.h"

class Spike : public Scenery {
public:
   static const std::string CLASS_NAME;
   static const float ATTACK_POWER;

   Spike(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
   virtual ~Spike();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

#include "CollisionsBoilerplateH.h"
};

#endif