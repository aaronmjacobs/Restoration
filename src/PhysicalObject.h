#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include "Geometry.h"

class Corona;
class Magus;
class Player;
class Scenery;

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

   virtual void collideWith(PhysicalObject &other) = 0;
   virtual void collideWith(Scenery &other) = 0;
   virtual void collideWith(Player &other) = 0;
   virtual void collideWith(Magus &other) = 0;
   virtual void collideWith(Corona &other) = 0;
};

#endif
