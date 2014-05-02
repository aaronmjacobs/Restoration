#include "FancyAssert.h"
#include "Shader.h"
#include "ShaderDeserializer.h"
#include "Types.h"

namespace ShaderDeserializer {

SPtr<Shader> deserialize(const Json::Value &root) {
   std::string typeName = root["type"].asString();
   GLenum type = 0;
   if (typeName == "vertex") {
      type = GL_VERTEX_SHADER;
   } else if (typeName == "fragment") {
      type = GL_FRAGMENT_SHADER;
   } else if (typeName == "geometry") {
      type = GL_GEOMETRY_SHADER;
   }
   ASSERT(type, "Invalid type name for shader: %s", typeName.c_str());

   std::string fileName = root["fileName"].asString();

   return std::make_shared<Shader>(type, fileName);
}

} // namespace ShaderDeserializer
