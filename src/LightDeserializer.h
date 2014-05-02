#ifndef LIGHT_DESERIALIZER_H
#define LIGHT_DESERIALIZER_H

#include "Types.h"

class Light;

namespace LightDeserializer {

SPtr<Light> deserialize(const Json::Value &root, SPtr<Scene> const scene);

} // namespace LightDeserializer

#endif
