#ifndef SHADER_PROGRAM_DESERIALIZER_H
#define SHADER_PROGRAM_DESERIALIZER_H

#include "Types.h"

class ShaderProgram;

namespace ShaderProgramDeserializer {

SPtr<ShaderProgram> deserialize(const std::string &fileName);

} // namespace ShaderProgramDeserializer

#endif
