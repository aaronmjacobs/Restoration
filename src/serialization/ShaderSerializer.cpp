#include "Serializer.h"
#include "ShaderSerializer.h"
#include "../engine/IOUtils.h"

#include <memory>

namespace ShaderSerializer {

ShaderRef load(const std::string &jsonFileName) {
   Json::Value root = IOUtils::readJsonFile(jsonFileName);

   Serializer::check(root, "type", "Shader");
   Serializer::check(root, "fileName", "Shader");

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

   return ShaderRef(std::make_shared<Shader>(jsonFileName, type, fileName));
}

} // namespace ShaderSerializer
