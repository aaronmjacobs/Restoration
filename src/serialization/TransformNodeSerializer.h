#ifndef TRANSFORM_NODE_SERIALIZER_H
#define TRANSFORM_NODE_SERIALIZER_H

#include "../engine/TransformNode.h"
#include "../engine/Scene.h"
#include "../engine/lib/json/json.h"

#include <string>

namespace TransformNodeSerializer {

TransformNodeRef load(const std::string &jsonFileName, Scene *scene);

TransformNodeRef deserialize(const Json::Value &root, Scene *scene);

} // namespace TransformNodeSerializer

#endif
