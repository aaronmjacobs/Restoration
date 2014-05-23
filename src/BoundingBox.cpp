#include "BoundingBox.h"
#include "FancyAssert.h"

BoundingBox::BoundingBox()
: xMin(0.0f), xMax(0.0f), yMin(0.0f), yMax(0.0f), zMin(0.0f), zMax(0.0f) {
}

BoundingBox::BoundingBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
   : xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax), zMin(zMin), zMax(zMax) {
}

BoundingBox::BoundingBox(const BoundingBox &source, const glm::vec3 &trans, const glm::vec3 &scale)
   : xMin(source.xMin * scale.x + trans.x), xMax(source.xMax * scale.x + trans.x), yMin(source.yMin * scale.y + trans.y), yMax(source.yMax * scale.y + trans.y), zMin(source.zMin * scale.z + trans.z), zMax(source.zMax * scale.z + trans.z) {
}

BoundingBox::BoundingBox(const BoundingBox &first, const BoundingBox &second)
   : xMin(glm::max(first.xMin, second.xMin)), xMax(glm::min(first.xMax, second.xMax)), yMin(glm::max(first.yMin, second.yMin)), yMax(glm::min(first.yMax, second.yMax)), zMin(glm::max(first.zMin, second.zMin)), zMax(glm::min(first.zMax, second.zMax)) {
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
   if (zMax < other.zMin || zMin > other.zMax) {
      return false;
   }
   return true;
}

bool BoundingBox::contains(const glm::vec3 &point) const {
   return xMin <= point.x && point.x <= xMax
       && yMin <= point.y && point.y <= yMax
       && zMin <= point.z && point.z <= zMax;
}

bool BoundingBox::completelyContains(const BoundingBox &other) const {
   return contains(other.min()) && contains(other.max());
}

float BoundingBox::height() const {
   return yMax - yMin;
}

float BoundingBox::width() const {
   return xMax - xMin;
}

float BoundingBox::depth() const {
   return zMax - zMin;
}

glm::vec3 BoundingBox::min() const {
   return glm::vec3(xMin, yMin, zMin);
}

glm::vec3 BoundingBox::max() const {
   return glm::vec3(xMax, yMax, zMax);
}

glm::vec3 BoundingBox::center() const {
   return glm::vec3(xMin + width() / 2.0f,
                    yMin + height() / 2.0f,
                    zMin + depth() / 2.0f);
}
