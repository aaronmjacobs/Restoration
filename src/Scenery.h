#ifndef SCENERY_H
#define SCENERY_H

#include "PhysicalObject.h"

class Scenery : public PhysicalObject {
public:
   static const std::string CLASS_NAME;

   Scenery(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
   virtual ~Scenery();

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
