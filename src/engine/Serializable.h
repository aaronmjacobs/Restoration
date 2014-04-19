#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <jsoncpp/json.h>
#include <memory>
#include <string>

class Serializable;
typedef std::shared_ptr<Serializable> SerializableRef;

class Serializable {
private:
   std::string jsonFileName;

public:
   Serializable(const std::string &jsonFileName)
      : jsonFileName(jsonFileName) {
   }

   virtual ~Serializable() {
   }

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const = 0;

   std::string getJsonFileName() const {
      return jsonFileName;
   }

   virtual std::string getJsonFolderName() const = 0;

   std::string getFullJsonPath() const {
      return getJsonFolderName() + getJsonFileName();
   }
};

#endif
