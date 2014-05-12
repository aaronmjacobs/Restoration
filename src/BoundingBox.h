#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "GLMIncludes.h"

class BoundingBox {
public:
   const float xMin, xMax, yMin, yMax, zMin, zMax;

   bool threeD = false;

   BoundingBox(float xMin, float xMax, float yMin, float yMax);
   BoundingBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
   BoundingBox(const BoundingBox &source, const glm::vec3 &trans, const glm::vec3 &scale);
   BoundingBox(const BoundingBox &first, const BoundingBox &second);
   virtual ~BoundingBox();

   bool collidesWith(const BoundingBox &other) const;
   bool contains(const glm::vec3 &point) const;
   float height() const;
   float width() const;
};

#endif
