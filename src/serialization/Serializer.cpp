#include "Serializer.h"
#include "../engine/IOUtils.h"

#include <iostream>

namespace Serializer {

void save(const Serializable &serializable) {
   std::string fileName = serializable.getFullJsonPath();
   std::cout << "Writing to: " << fileName << std::endl;
   IOUtils::writeJsonFile(serializable.serialize(), fileName);
}

void check(const Json::Value &value, const char *key, const char *type) {
   //ASSERT(value[key], "Missing key during deserialization of %s: %s", type, key);
}

} // namespace Serializer
