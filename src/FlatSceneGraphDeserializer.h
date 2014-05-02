#ifndef FLAT_SCENE_GRAPH_DESERIALIZER_H
#define FLAT_SCENE_GRAPH_DESERIALIZER_H

#include "Types.h"

class FlatSceneGraph;
class Scene;

namespace FlatSceneGraphDeserializer {

SPtr<FlatSceneGraph> deserialize(const Json::Value &root, SPtr<Scene> scene);

} // namespace FlatSceneGraphDeserializer

#endif
