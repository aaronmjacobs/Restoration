#include "Serializer.h"
#include "../engine/IOUtils.h"

namespace Serializer {

void save(const Serializable &serializable, const std::string &fileName) {
   IOUtils::writeJsonFile(serializable.serialize(), fileName);
}

void check(const Json::Value &value, const char *key, const char *type) {
   ASSERT(value[key], "Missing key during deserialization of %s: %s", type, key);
}

} // namespace Serializer
