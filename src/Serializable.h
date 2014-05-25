#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "lib/json/json.h"

class Serializable {
public:
   const std::string CLASS_NAME = "Serializable";

   Serializable() {
   }

   virtual ~Serializable() {
   }

   virtual bool shouldBeSerialized() {
      return true;
   }

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const = 0;
};

#endif
