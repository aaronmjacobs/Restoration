#include "PhysicalObject.h"

bool PhysicalObject::checkCollision(PhysicalObjectRef physObj) {
   //check if objects are on screen via clipping and culling
   if (this->xMax < physObj->xMin || this->xMin > physObj->xMax)
      return false;
   if (this->yMax < physObj->yMin || this->yMin > physObj->yMax)
      return false;
   return true;
}