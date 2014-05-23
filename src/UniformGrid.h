#ifndef UNIFORM_GRID_H
#define UNIFORM_GRID_H

#include "BoundingBox.h"
#include "FancyAssert.h"
#include "GLMIncludes.h"

#include <vector>

template<class T>
struct GridElement {
   T element;
   std::vector<size_t> nodes;
};

template<class T>
struct GridNode {
   std::vector<T> elements;
};

template<class T>
class UniformGrid {
protected:
   const glm::vec2 min, max;
   const size_t numHoriz, numVert;
   std::vector<GridElement<T>> gridElements;
   std::vector<GridNode<T>> nodes;

   size_t getNodeIndex(const glm::vec2 point) const {
      // Woo, floating point inprecision!
      float xPercent = glm::clamp<float>((point.x - min.x) / (max.x - min.x), 0.0f, 0.999f);
      float yPercent = glm::clamp<float>((point.y - min.y) / (max.y - min.y), 0.0f, 0.999f);

      size_t gridX = xPercent * numHoriz;
      size_t gridY = yPercent * numVert;
      size_t index = gridX + gridY * numHoriz;
      ASSERT(index < nodes.size(), "Invalid grid index");
      return index;
   }

   void addToNode(GridElement<T> &gridElement, const size_t index) {
      gridElement.nodes.push_back(index);
      nodes[index].elements.push_back(gridElement.element);
   }

public:
   UniformGrid(size_t numHoriz, size_t numVert, glm::vec2 min, glm::vec2 max)
   : min(min), max(max), numHoriz(numHoriz), numVert(numVert), nodes(numHoriz * numVert) {
   }

   virtual ~UniformGrid() {
   }

   void insert(T& element) {
      GridElement<T> gridElement;
      gridElement.element = element;

      // TODO Calculate node indices for the min / max corners of the bounds
      // TODO If they match, just put the element in the single node
      // TODO If they do NOT match, calculate the rest of the corners, and determine
      // TODO All the nodes the object should be in
      glm::vec3 elementPos = element->getBounds().center();
      size_t index = getNodeIndex(glm::vec2(elementPos.x, elementPos.y));
      addToNode(gridElement, index);
      gridElements.push_back(gridElement);
   }

   void update() {
      for (typename std::vector<GridElement<T>>::iterator itr = gridElements.begin(); itr != gridElements.end();) {
         if (itr->element->shouldBeRemoved()) {
            itr = gridElements.erase(itr);
         } else {
            ++itr;
         }
      }
   }
};

#endif
