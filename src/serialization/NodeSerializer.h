#ifndef NODE_SERIALIZER_H
#define NODE_SERIALIZER_H

#include "../engine/SceneNode.h"
#include "../engine/Scene.h"
#include "../engine/lib/json/json.h"

#include <string>

namespace NodeSerializer {

NodeRef load(const std::string &jsonFileName, Scene *scene);

NodeRef deserialize(const Json::Value &root, Scene *scene);

} // namespace NodeSerializer

#endif
