#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include "BoundingBox.h"
#include "Geometry.h"

class MovableObject;

class PhysicalObject : public Geometry {
protected:
   BoundingBox bounds;

public:
   PhysicalObject(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
   virtual ~PhysicalObject();

   BoundingBox getBounds() const;
   bool collidesWith(const PhysicalObject &other) const;
   float height() const;
   float width() const;

   virtual void collideWith(PhysicalObject &other) = 0;
   virtual void collideWith(MovableObject &other) = 0;
};

#endif
