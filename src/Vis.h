// Energy shot

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

#endif
