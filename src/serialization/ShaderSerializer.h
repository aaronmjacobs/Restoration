#ifndef SHADER_SERIALIZER_H
#define SHADER_SERIALIZER_H

#include "../engine/Shader.h"

#include "../engine/lib/json/json.h"
#include <string>

namespace ShaderSerializer {

Json::Value serialize(const Shader &shader);
ShaderRef deserialize(const Json::Value &root);

void save(const Shader &shader, const std::string &fileName);
ShaderRef load(const std::string &fileName);

} // namespace ShaderSerializer

#endif
