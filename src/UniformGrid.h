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

   size_t getNodeIndex(size_t gridX, size_t gridY) const {
      return gridX + gridY * numHoriz;
   }

   size_t getNodeIndex(const glm::vec2 point) const {
      // Woo, floating point inprecision! Also, keeps elements bound to the world (anything outside of
      // the grid gets place in the grid node thy are closest to).
      float xPercent = glm::clamp<float>((point.x - min.x) / (max.x - min.x), 0.0f, 0.999f);
      float yPercent = glm::clamp<float>((point.y - min.y) / (max.y - min.y), 0.0f, 0.999f);

      size_t gridX = xPercent * numHoriz;
      size_t gridY = yPercent * numVert;
      size_t index = getNodeIndex(gridX, gridY);
      ASSERT(index >= 0 && index < nodes.size(), "Invalid grid index");
      return index;
   }

   void getNodeCoordinates(const size_t index, size_t *x, size_t *y) const {
      *x = index % numHoriz;
      *y = index / numHoriz;
   }

   std::vector<size_t> getContainingNodes(const T& element) const {
      BoundingBox bounds = element->getBounds();
      size_t minNodeX, minNodeY, maxNodeX, maxNodeY;
      getNodeCoordinates(getNodeIndex(glm::vec2(bounds.min().x, bounds.min().y)), &minNodeX, &minNodeY);
      getNodeCoordinates(getNodeIndex(glm::vec2(bounds.max().x, bounds.max().y)), &maxNodeX, &maxNodeY);

      std::vector<size_t> containingNodes;
      for (size_t y = minNodeY; y <= maxNodeY; ++y) {
         for (size_t x = minNodeX; x <= maxNodeX; ++x) {
            containingNodes.push_back(getNodeIndex(x, y));
         }
      }

      return containingNodes;
   }

   void addToNode(GridElement<T> &gridElement, const size_t index) {
      gridElement.nodes.push_back(index);
      nodes[index].elements.push_back(gridElement.element);
   }

   void removeFromNode(GridElement<T> &gridElement, const size_t index) {
      // Remove the index from the GridElement
      typename std::vector<size_t>::iterator location = std::find(gridElement.nodes.begin(), gridElement.nodes.end(), index);
      ASSERT(location != gridElement.nodes.end(), "Unable to find node index in GridElement: %lu", index);
      gridElement.nodes.erase(location);

      // Remove the element from the GridNode
      typename std::vector<T>::iterator elementLocation = std::find(nodes[index].elements.begin(), nodes[index].elements.end(), gridElement.element);
      ASSERT(elementLocation != nodes[index].elements.end(), "Unable to find element in GridNode");
      nodes[index].elements.erase(elementLocation);
   }

   void place(GridElement<T> &gridElement) {
      std::vector<size_t> correctNodes = getContainingNodes(gridElement.element);
      std::vector<size_t> currentNodes = gridElement.nodes;

      // Remove the element from any nodes it is currently in, but should not be in
      for (size_t currentNode : currentNodes) {
         if (std::find(correctNodes.begin(), correctNodes.end(), currentNode) == currentNodes.end()) {
            removeFromNode(gridElement, currentNode);
         }
      }

      // Put the element in any nodes it should be in, and isn't already in
      for (size_t correctNode : correctNodes) {
         if (std::find(currentNodes.begin(), currentNodes.end(), correctNode) == currentNodes.end()) {
            addToNode(gridElement, correctNode);
         }
      }
   }

public:
   UniformGrid(size_t numHoriz, size_t numVert, glm::vec2 min, glm::vec2 max)
   : min(min), max(max), numHoriz(numHoriz), numVert(numVert), nodes(numHoriz * numVert) {
   }

   virtual ~UniformGrid() {
   }

   void insert(T& element) {
      // Create a new grid element
      GridElement<T> gridElement;
      gridElement.element = element;

      // Place the elemnt inside the correct grid nodes based on its position and bounding box
      place(gridElement);

      // Add to the list of grid elements
      gridElements.push_back(gridElement);
   }

   void update() {
      for (typename std::vector<GridElement<T>>::iterator itr = gridElements.begin(); itr != gridElements.end();) {
         // Erase any elements that should be removed
         if (itr->element->shouldBeRemoved()) {
            // Remove it from each grid node
            while (!itr->nodes.empty()) {
               removeFromNode(*itr, itr->nodes[0]);
            }

            // Erase the element
            itr = gridElements.erase(itr);
            continue;
         }

         // Place the elemnt inside the correct grid nodes based on its position and bounding box
         place(*itr);

         ++itr;
      }
   }

   std::vector<GridElement<T>>& getElements() {
      return gridElements;
   }

   std::vector<GridNode<T>>& getNodes() {
      return nodes;
   }
};

#endif
