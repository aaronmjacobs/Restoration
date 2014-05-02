#ifndef SCENE_GRAPH_DESERIALIZER_H
#define SCENE_GRAPH_DESERIALIZER_H

#include "Types.h"

class Scene;
class SceneGraph;

namespace SceneGraphDeserializer {

SPtr<SceneGraph> deserialize(const Json::Value &root, SPtr<Scene> scene);

} // namespace SceneGraphDeserializer

#endif
