#ifndef MESH_DESERIALIZER_H
#define MESH_DESERIALIZER_H

#include "Types.h"
#include "lib/json/json.h"

class Mesh;

namespace MeshDeserializer {

SPtr<Mesh> deserialize(const Json::Value &root);

} // namespace MeshDeserializer

#endif
