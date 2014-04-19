#include "Serializer.h"
#include "ShaderSerializer.h"
#include "../engine/IOUtils.h"

#include <memory>

namespace ShaderSerializer {

Json::Value serialize(const Shader &shader) {
   Json::Value root;

   root["id"] = shader.getID();
   root["fileName"] = shader.getFileName();

   return root;
}

ShaderRef deserialize(const Json::Value &root) {
   Serializer::check(root, "id", "Shader");
   Serializer::check(root, "fileName", "Shader");
   GLuint id = root["id"].asUInt();
   std::string fileName = root["fileName"].asString();

   return ShaderRef(std::make_shared<Shader>(id, fileName));
}

void save(const Shader &shader, const std::string &fileName) {
   IOUtils::writeJsonFile(serialize(shader), fileName);
}

ShaderRef load(const std::string &fileName) {
   return deserialize(IOUtils::readJsonFile(fileName));
}

} // namespace ShaderSerializer
