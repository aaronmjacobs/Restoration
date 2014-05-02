#ifndef SCENE_DESERIALIZER_H
#define SCENE_DESERIALIZER_H

#include "Types.h"

class Scene;

namespace SceneDeserializer {

SPtr<Scene> deserialize(const std::string &fileName);

} // namespace SceneDeserializer

#endif
