#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "lib/json/json.h"

class Serializable {
protected:
   bool shouldSerialize;

public:
   const std::string CLASS_NAME = "Serializable";

   Serializable() {
      shouldSerialize = true;
   }

   virtual ~Serializable() {
   }

   virtual bool shouldBeSerialized() {
      return shouldSerialize;
   }

   virtual void shouldBeSerialized(bool serialize) {
      shouldSerialize = serialize;
   }

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const = 0;
};

#endif
