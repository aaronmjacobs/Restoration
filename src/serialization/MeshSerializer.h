#ifndef MESH_SERIALIZER_H
#define MESH_SERIALIZER_H

#include "../engine/Mesh.h"

#include "../engine/lib/json/json.h"
#include <string>

namespace MeshSerializer {

MeshRef load(const std::string &jsonFileName);

} // namespace MeshSerializer

#endif
