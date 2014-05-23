#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include "FancyAssert.h"

#include <list>

template<class T>
class PoolAllocator {
protected:
   static PoolAllocator<T> instance;
   std::list<T> allocated;
   std::list<T> freed;

public:
   static PoolAllocator<T>& getInstance();
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

template<class T>
PoolAllocator<T> PoolAllocator<T>::instance;

template<class T>
PoolAllocator<T>& PoolAllocator<T>::getInstance() {
   return instance;
}

#endif
