#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "PhysicalObject.h"

class Checkpoint : public PhysicalObject {
public:
   static const std::string CLASS_NAME;

   Checkpoint(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
   virtual ~Checkpoint();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   /**
    * Steps |dt| seconds through time.
    */
   virtual void tick(const float dt);

#include "CollisionsBoilerplateH.h"
};

#endif
