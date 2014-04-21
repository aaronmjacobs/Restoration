#include "PhysicalObject.h"


PhysicalObject::PhysicalObject(const std::string &jsonFileName, const std::string &name, ModelRef model)
: GeometryNode(jsonFileName, name, model) {
}

PhysicalObject::~PhysicalObject() {
}

// MAKE RELATIVE
// make four variables xmax xmin ymin ymax relative positions

bool PhysicalObject::checkCollision(PhysicalObjectRef physObj) {
   float relXMin = this->position.x + this->xMin;
   float relXMax = this->position.x + this->xMax;
   float relYMin = this->position.y + this->yMin;
   float relYMax = this->position.y + this->yMax;
   float oRelXMin = physObj->position.x + physObj->xMin;
   float oRelXMax = physObj->position.x + physObj->xMax;
   float oRelYMin = physObj->position.y + physObj->yMin;
   float oRelYMax = physObj->position.y + physObj->yMax;
   //check if objects are on screen via clipping and culling
   if (relXMax < oRelXMin || relXMin > oRelXMax)
      return false;
   if (relYMax < oRelYMin || relYMin > oRelYMax)
      return false;
   return true;
}