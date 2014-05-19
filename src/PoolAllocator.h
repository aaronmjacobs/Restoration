#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include "FancyAssert.h"

#include <vector>

template<class T>
class PoolAllocator {
protected:
   std::vector<T> allocated;
   std::vector<T> freed;

public:
   PoolAllocator(const size_t initialSize = 0)
   : freed(initialSize) {
   }

   virtual ~PoolAllocator() {
   }

   T& alloc() {
      if(!freed.empty()) {
         // Allocate from the free list
         T& element = freed.back();
         freed.pop_back();
         allocated.push_back(element);
         return element;
      }

      printf("Allocating\n");
      // Allocate a new object
      T element;
      allocated.push_back(element);
      return allocated.back();
   }

   void reset() {
      // Move all items from allocated list to freed list
      while (!allocated.empty()) {
         T& element = allocated.back();
         allocated.pop_back();
         freed.push_back(element);
      }
   }
};

#endif
