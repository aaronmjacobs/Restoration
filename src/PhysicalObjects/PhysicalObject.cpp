#include "PhysicalObject.h"

std::list<PhysicalObject*> PhysicalObject::physicalObjects;

PhysicalObject::PhysicalObject(const std::string &jsonFileName, const std::string &name, ModelRef model)
: GeometryNode(jsonFileName, name, model) {
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

bool PhysicalObject::checkCollision(PhysicalObjectRef physObj) {
   AxisAlignedBoundingBox tBounds = getBounds();
   AxisAlignedBoundingBox oBounds = physObj->getBounds();

   //check if objects are on screen via clipping and culling
   if (tBounds.xMax < oBounds.xMin || tBounds.xMin > oBounds.xMax)
      return false;
   if (tBounds.yMax < oBounds.yMin || tBounds.yMin > oBounds.yMax)
      return false;
   return true;
}
