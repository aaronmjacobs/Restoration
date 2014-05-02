#include "FancyAssert.h"
#include "IOUtils.h"
#include "ShaderDeserializer.h"
#include "ShaderProgram.h"
#include "ShaderProgramDeserializer.h"
#include "Types.h"

namespace ShaderProgramDeserializer {

SPtr<ShaderProgram> deserialize(const std::string &fileName) {
   SPtr<ShaderProgram> shaderProgram = std::make_shared<ShaderProgram>(fileName);
   Json::Value root = IOUtils::readJsonFile(IOUtils::getPath<ShaderProgram>(fileName));

   // Load each shader
   Json::Value shadersVal = root["shaders"];
   ASSERT(shadersVal.isArray(), "shaders should be an array");
   for (int i = 0; i < shadersVal.size(); ++i) {
      shaderProgram->attach(ShaderDeserializer::deserialize(shadersVal[i]));
   }

   // Compile and link the shaders
   shaderProgram->compileShaders();
   shaderProgram->link();

   // Load all attributes
   Json::Value attribsVal = root["attributes"];
   ASSERT(attribsVal.isArray(), "attributes should be an array");
   for (int i = 0; i < attribsVal.size(); ++i) {
      shaderProgram->addAttribute(attribsVal[i].asString());
   }

   // Load all uniforms
   Json::Value uniformsVal = root["uniforms"];
   ASSERT(uniformsVal.isArray(), "uniforms should be an array");
   for (int i = 0; i < uniformsVal.size(); ++i) {
      shaderProgram->addUniform(uniformsVal[i].asString());
   }

   return shaderProgram;
}

} // namespace ShaderProgramDeserializer
