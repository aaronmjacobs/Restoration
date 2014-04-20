#ifndef GEOMETRY_NODE_SERIALIZER_H
#define GEOMETRY_NODE_SERIALIZER_H

#include "../engine/GeometryNode.h"
#include "../engine/Scene.h"
#include "../engine/lib/json/json.h"

#include <string>

namespace GeometryNodeSerializer {

GeometryNodeRef load(const std::string &jsonFileName, Scene *scene);

GeometryNodeRef deserialize(const Json::Value &root, Scene *scene);

} // namespace GeometryNodeSerializer

#endif
