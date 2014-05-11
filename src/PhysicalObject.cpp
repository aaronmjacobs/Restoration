#include "Mesh.h"
#include "Model.h"
#include "PhysicalObject.h"

const std::string PhysicalObject::CLASS_NAME = "PhysicalObject";

PhysicalObject::PhysicalObject(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
   : Geometry(scene, model, name), bounds(*model->getMesh()->getBounds()) {
}

PhysicalObject::~PhysicalObject() {
}

Json::Value PhysicalObject::serialize() const {
   Json::Value root = Geometry::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

BoundingBox PhysicalObject::getBounds() const {
   return BoundingBox(bounds, position, scale);
}

bool PhysicalObject::collidesWith(const PhysicalObject &other) const { 
   return getBounds().collidesWith(other.getBounds());
}
