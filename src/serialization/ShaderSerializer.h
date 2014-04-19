#ifndef SHADER_SERIALIZER_H
#define SHADER_SERIALIZER_H

#include "../engine/Shader.h"

#include "../engine/lib/json/json.h"
#include <string>

namespace ShaderSerializer {

ShaderRef load(const std::string &jsonFileName);

} // namespace ShaderSerializer

#endif
