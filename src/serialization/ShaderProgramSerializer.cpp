#include "ShaderProgramSerializer.h"
#include "Serializer.h"
#include "../engine/IOUtils.h"

#include <memory>

namespace ShaderProgramSerializer {

ShaderProgramRef load(const std::string &jsonFileName) {
   Json::Value root = IOUtils::readJsonFile(jsonFileName);

   ShaderProgramRef shaderProgram(std::make_shared<ShaderProgram>(jsonFileName));

   // Load each shader
   Serializer::check(root, "shaders", "ShaderProgram");
   Json::Value shadersVal = root["shaders"];
   ASSERT(shadersVal.isArray(), "shaders should be an array");
   for (int i = 0; i < shadersVal.size(); ++i) {
      std::string shaderJsonFileName = shadersVal[i].asString();

      // TODO Make shaders reusable (save in a global map / list?)
      ShaderRef shader = ShaderSerializer::load(shaderJsonFileName);
      shaderProgram->attach(shader);
   }

   // Compile and link the shaders
   shaderProgram->compileShaders();
   shaderProgram->link();

   // Load all attributes
   Serializer::check(root, "attributes", "ShaderProgram");
   Json::Value attribsVal = root["attributes"];
   ASSERT(attribsVal.isArray(), "attributes should be an array");
   for (int i = 0; i < attribsVal.size(); ++i) {
      std::string attribName = attribsVal[i].asString();
      shaderProgram->addAttribute(attribName);
   }

   // Load all uniforms
   Serializer::check(root, "uniforms", "ShaderProgram");
   Json::Value uniformsVal = root["uniforms"];
   ASSERT(uniformsVal.isArray(), "uniforms should be an array");
   for (int i = 0; i < uniformsVal.size(); ++i) {
      std::string uniformName = uniformsVal[i].asString();
      shaderProgram->addUniform(uniformName);
   }

   return shaderProgram;
}

} // namespace ShaderProgramSerializer