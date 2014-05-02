#include "BoundingBox.h"
#include "FancyAssert.h"

BoundingBox::BoundingBox(float xMin, float xMax, float yMin, float yMax)
   : xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax) {
}

BoundingBox::BoundingBox(const BoundingBox &source, const glm::vec3 &trans)
   : xMin(source.xMin + trans.x), xMax(source.xMax + trans.x), yMin(source.yMin + trans.y), yMax(source.yMax + trans.y) {
}

BoundingBox::BoundingBox(const BoundingBox &first, const BoundingBox &second)
   : xMin(glm::max(first.xMin, second.xMin)), xMax(glm::min(first.xMax, second.xMax)), yMin(glm::max(first.yMin, second.yMin)), yMax(glm::min(first.yMax, second.yMax)) {
   ASSERT(first.collidesWith(second), "Trying to generate collision box from non-colliding bounding boxes");
}

BoundingBox::~BoundingBox() {
}

bool BoundingBox::collidesWith(const BoundingBox &other) const {
   if (xMax < other.xMin || xMin > other.xMax) {
      return false;
   }
   if (yMax < other.yMin || yMin > other.yMax) {
      return false;
   }
   return true;
}
