#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include "Geometry.h"
#include "CollisionsDeclarations.h"

class PhysicalObject : public Geometry {
public:
   static const std::string CLASS_NAME;

   PhysicalObject(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
   virtual ~PhysicalObject();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   virtual bool canMove() {
      return false;
   }

   bool collidesWith(const PhysicalObject &other) const;

#define COLLISION_PURE_VIRTUAL
#include "CollisionsBoilerplateH.h"
};

#endif
