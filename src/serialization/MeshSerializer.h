#ifndef MESH_SERIALIZER_H
#define MESH_SERIALIZER_H

#include "../engine/Mesh.h"

#include <jsoncpp/json.h>
#include <string>

namespace MeshSerializer {

Json::Value serialize(const Mesh &mesh);
MeshRef deserialize(const Json::Value &root);

void save(const Mesh &mesh, const std::string &fileName);
MeshRef load(const std::string &fileName);

} // namespace MeshSerializer

#endif
