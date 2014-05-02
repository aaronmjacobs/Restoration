#ifndef SCENE_OBJECT_DESERIALIZER_H
#define SCENE_OBJECT_DESERIALIZER_H

#include "Types.h"

class SceneObject;

namespace SceneObjectDeserializer {

SPtr<SceneObject> deserialize(const Json::Value &root, SPtr<Scene> const scene);

} // namespace SceneObjectDeserializer

#endif
