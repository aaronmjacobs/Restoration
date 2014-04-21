#include "PhysicalObject.h"

std::list<PhysicalObject*> PhysicalObject::physicalObjects;

PhysicalObject::PhysicalObject(Scene *scene, const std::string &jsonFileName, const std::string &name, ModelRef model)
: GeometryNode(scene, jsonFileName, name, model) {
   physicalObjects.push_back(this);
}

PhysicalObject::~PhysicalObject() {
   physicalObjects.remove(this);
}

AxisAlignedBoundingBox PhysicalObject::getBounds() {
   AxisAlignedBoundingBox absoluteBounds = boundingBox;

   absoluteBounds.xMin += position.x;
   absoluteBounds.xMax += position.x;
   absoluteBounds.yMin += position.y;
   absoluteBounds.yMax += position.y;

   return absoluteBounds;
}

bool PhysicalObject::checkCollision(PhysicalObject *physObj) {
   AxisAlignedBoundingBox tBounds = getBounds();
   AxisAlignedBoundingBox oBounds = physObj->getBounds();

   float give = 0.01f;

   //check if objects are on screen via clipping and culling
   if (tBounds.xMax - give < oBounds.xMin || tBounds.xMin + give > oBounds.xMax)
      return false;
   if (tBounds.yMax < oBounds.yMin || tBounds.yMin > oBounds.yMax)
      return false;
   return true;
}
