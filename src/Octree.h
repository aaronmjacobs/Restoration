#ifndef OCTREE_H
#define OCTREE_H

#include "Types.h"

#include <list>

template <class T>
class Octree {
protected:
   const unsigned int MAX_ELEMENTS;
   std::list<T> elements;

public:
   Octree(const unsigned int maxElements)
   : MAX_ELEMENTS(maxElements) {
   }

   virtual ~Octree() {
   }

   void add(T element) {
      if (elements.size() < MAX_ELEMENTS) {
         elements.push_back(element);
         return;
      } else if (IF DOES NOT HAVE CHILDREN) {
         // TODO Create children
      }

      // TODO Add element to child
   }
};

#endif
