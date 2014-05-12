#ifndef SAVEABLE_H
#define SAVEABLE_H

#include "Serializable.h"

#include <string>

class Saveable : public Serializable {
private:
   const std::string jsonFileName;

public:
   Saveable(const std::string &jsonFileName)
      : jsonFileName(jsonFileName) {
   }

   Saveable() {
   }

   ~Saveable() {
   }

   /**
    * Gets the name of the json file the serializable will be written to.
    */
   std::string getJsonFileName() const {
      return jsonFileName;
   }
};

#endif
