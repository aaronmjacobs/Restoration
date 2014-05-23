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

   return std::make_shared<BoundingBox>(min.x - 1.0f, max.x + 1.0f, min.y - 1.0f, max.y + 1.0f, min.z - 1.0f, max.z + 1.0f);
}

} // namespace

template <class T>
class Octree {
protected:
   const unsigned int MAX_ELEMENTS;
   const unsigned int level;
   SPtr<BoundingBox> bounds;
   SPtr<Octree<T>> children[NUM_CHILDREN];
   std::vector<T> elements;

   explicit Octree(const unsigned int maxElements, const unsigned int level, const BoundingBox &bounds)
   : MAX_ELEMENTS(maxElements), level(level), bounds(std::make_shared<BoundingBox>(bounds)) {
   }

   void add(T element) {
      if (elements.size() == MAX_ELEMENTS) {
         // Create / initialize children
         initChildren();
      }

      if (hasChildren()) {
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
      for (size_t octant = 0; octant < NUM_CHILDREN; ++octant) {
         children[octant] = SPtr<Octree<T>>(new Octree<T>(MAX_ELEMENTS, level + 1, determineBounds(octant)));
      }

      // If an element fits completely into a child, move it to the child. Otherwise, keep it in the parent.
      for (typename std::vector<T>::iterator itr = elements.begin(); itr != elements.end();) {
         glm::vec3 elementCenter = (*itr)->getBounds().center();
         size_t octant = getOctantContainingPoint(elementCenter);

         if (fitsInsideChild(*itr, octant)) {
            children[octant]->add(*itr);
            itr = elements.erase(itr);
         } else {
            ++itr;
         }
      }
   }

   void insertIntoChild(T element) {
      glm::vec3 elementCenter = element->getBounds().center();

      size_t octant = getOctantContainingPoint(elementCenter);
      if (fitsInsideChild(element, octant)) {
         children[octant]->add(element);
      } else {
         elements.push_back(element);
      }
   }

   inline bool fitsInsideChild(T element, size_t octant) {
      return children[octant]->bounds->completelyContains(element->getBounds());
   }

   BoundingBox determineBounds(size_t octant) {
      float minX, maxX, minY, maxY, minZ, maxZ;
      glm::vec3 parentMin = bounds->min();
      glm::vec3 parentMax = bounds->max();
      glm::vec3 parentCenter = bounds->center();

      if (octant & 4) {
         // Positive x
         minX = parentCenter.x;
         maxX = parentMax.x;
      } else {
         // Negative x
         minX = parentMin.x;
         maxX = parentCenter.x;
      }

      if (octant & 2) {
         // Positive y
         minY = parentCenter.y;
         maxY = parentMax.y;
      } else {
         // Negative y
         minY = parentMin.y;
         maxY = parentCenter.y;
      }

      if (octant & 1) {
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

   size_t getOctantContainingPoint(const glm::vec3& point) const {
      glm::vec3 center = bounds->center();
      size_t oct = 0;
      if(point.x >= center.x) oct |= 4;
      if(point.y >= center.y) oct |= 2;
      if(point.z >= center.z) oct |= 1;
      return oct;
   }

public:
   explicit Octree(const unsigned int maxElements, const std::vector<T> &elements)
   : MAX_ELEMENTS(maxElements), bounds(calcBounds(elements)), level(0) {
      for (T element : elements) {
         add(element);
      }
   }

   virtual ~Octree() {
   }

   bool hasChildren() {
      return !!children[0];
   }

   SPtr<Octree<T>> getChild(size_t octant) {
      return children[octant];
   }

   std::vector<T>& getElements() {
      return elements;
   }
};

#endif
