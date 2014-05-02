#include "FancyAssert.h"
#include "Mesh.h"
#include "MeshDeserializer.h"
#include "Types.h"

namespace MeshDeserializer {

SPtr<Mesh> deserialize(const Json::Value &root) {
   return std::make_shared<Mesh>(root["fileName"].asString());
}

} // namespace MeshDeserializer
