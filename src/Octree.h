#ifndef OCTREE_H
#define OCTREE_H

#include "BoundingBox.h"
#include "GLMIncludes.h"
#include "Types.h"

#include <vector>

#define NUM_CHILDREN 8

namespace {

template<class T>
SPtr<BoundingBox> calcBounds(const std::vector<T> &objects) {
   ASSERT(!objects.empty(), "No objects to calc bounds from");

   glm::vec3 min, max;
   BoundingBox firstBounds = objects[0]->getBounds();
   min = firstBounds.min();
   max = firstBounds.max();

   for (T object : objects) {
      BoundingBox objectBounds = object->getBounds();
      glm::vec3 objMin = objectBounds.min();
      glm::vec3 objMax = objectBounds.max();

      if (objMin.x < min.x) {
         min.x = objMin.x;
      }
      if (objMin.y < min.y) {
         min.y = objMin.y;
      }
      if (objMin.z < min.z) {
         min.z = objMin.z;
      }
      if (objMax.x > max.x) {
         max.x = objMax.x;
      }
      if (objMax.y > max.y) {
         max.y = objMax.y;
      }
      if (objMax.z > max.z) {
         max.z = objMax.z;
      }
   }

   return std::make_shared<BoundingBox>(min.x, max.x, min.y, max.y, min.z, max.z);
}

BoundingBox determineBounds(const BoundingBox &parent, size_t index) {
   float minX, maxX, minY, maxY, minZ, maxZ;
   glm::vec3 parentMin = parent.min();
   glm::vec3 parentMax = parent.max();
   glm::vec3 parentCenter = parent.center();

   if (index & 4) {
      // Positive x
      minX = parentCenter.x;
      maxX = parentMax.x;
   } else {
      // Negative x
      minX = parentMin.x;
      maxX = parentCenter.x;
   }

   if (index & 2) {
      // Positive y
      minY = parentCenter.y;
      maxY = parentMax.y;
   } else {
      // Negative y
      minY = parentMin.y;
      maxY = parentCenter.y;
   }

   if (index & 1) {
      // Positive z
      minZ = parentCenter.z;
      maxZ = parentMax.z;
   } else {
      // Negative z
      minZ = parentMin.z;
      maxZ = parentCenter.z;
   }

   return BoundingBox(minX, maxX, minY, maxY, minZ, maxZ);
}

} // namespace

template <class T>
class Octree {
protected:
   const unsigned int MAX_ELEMENTS;
   SPtr<BoundingBox> bounds;
   SPtr<Octree<T>> children[NUM_CHILDREN];
   std::vector<T> elements;

   explicit Octree(const unsigned int maxElements, const BoundingBox &bounds)
   : MAX_ELEMENTS(maxElements), bounds(std::make_shared<BoundingBox>(bounds)) {
   }

   void add(T element) {
      if (elements.size() == MAX_ELEMENTS) {
         // Create / initialize children
         initChildren();
      }

      if (children[0]) {
         // Add element to child
         insertIntoChild(element);
      } else {
         // Add to elements
         elements.push_back(element);
      }
   }

   void initChildren() {
      // TODO Use allocator to avoid a large number of heap allocations?

      // Create children
      for (size_t i = 0; i < NUM_CHILDREN; ++i) {
         children[i] = SPtr<Octree<T>>(new Octree<T>(MAX_ELEMENTS, determineBounds(*bounds, i)));
      }

      // Copy each element into a child
      for (T element : elements) {
         insertIntoChild(element);
      }

      // Clear the elements of this tree
      elements.clear();
   }

   void insertIntoChild(T element) {
      BoundingBox elementBounds = element->getBounds();
      glm::vec3 treeCenter = bounds->center();
      glm::vec3 elementCenter = elementBounds.center();

      if (elementCenter.x < treeCenter.x) {
         if (elementCenter.y < treeCenter.y) {
            if (elementCenter.z < treeCenter.z) {
               children[0]->add(element);
            } else {
               children[1]->add(element);
            }
         } else {
            if (elementCenter.z < treeCenter.z) {
               children[2]->add(element);
            } else {
               children[3]->add(element);
            }
         }
      } else {
         if (elementCenter.y < treeCenter.y) {
            if (elementCenter.z < treeCenter.z) {
               children[4]->add(element);
            } else {
               children[5]->add(element);
            }
         } else {
            if (elementCenter.z < treeCenter.z) {
               children[6]->add(element);
            } else {
               children[7]->add(element);
            }
         }
      }
   }

public:
   explicit Octree(const unsigned int maxElements, const std::vector<T> &elements)
   : MAX_ELEMENTS(maxElements), bounds(calcBounds(elements)) {
      for (T element : elements) {
         add(element);
      }
   }

   virtual ~Octree() {
   }
};

#endif
