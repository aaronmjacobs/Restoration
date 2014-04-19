#ifndef SHADER_PROGRAM_SERIALIZER_H
#define SHADER_PROGRAM_SERIALIZER_H

#include "../engine/ShaderProgram.h"

#include <jsoncpp/json.h>
#include <string>

namespace ShaderProgramSerializer {

ShaderProgramRef load(const std::string &jsonFileName);

} // namespace ShaderProgramSerializer

#endif
