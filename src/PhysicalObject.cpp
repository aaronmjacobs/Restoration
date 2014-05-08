#include "Mesh.h"
#include "Model.h"
#include "PhysicalObject.h"

PhysicalObject::PhysicalObject(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
   : Geometry(scene, model, name), bounds(*model->getMesh()->getBounds()) {
   this->renderState = LIGHTWORLD_STATE;
}

PhysicalObject::~PhysicalObject() {
}

BoundingBox PhysicalObject::getBounds() const {
   return BoundingBox(bounds, position, scale);
}

bool PhysicalObject::collidesWith(const PhysicalObject &other) const { 
   return getBounds().collidesWith(other.getBounds());
}
