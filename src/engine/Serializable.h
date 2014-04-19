#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "lib/json/json.h"
#include <memory>

class Serializable;
typedef std::shared_ptr<Serializable> SerializableRef;

class Serializable {
public:
   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const = 0;
};

#endif
