#ifndef SHADER_DESERIALIZER_H
#define SHADER_DESERIALIZER_H

#include "Types.h"

class Shader;

namespace ShaderDeserializer {

SPtr<Shader> deserialize(const Json::Value &root);

} // namespace ShaderDeserializer

#endif
