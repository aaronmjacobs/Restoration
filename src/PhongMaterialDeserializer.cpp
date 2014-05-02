#include "FancyAssert.h"
#include "IOUtils.h"
#include "PhongMaterial.h"
#include "PhongMaterialDeserializer.h"
#include "Scene.h"
#include "ShaderProgram.h"
#include "ShaderProgramDeserializer.h"
#include "Types.h"

namespace PhongMaterialDeserializer {

SPtr<PhongMaterial> deserialize(const std::string &fileName, SPtr<Scene> scene) {
   Json::Value root = IOUtils::readJsonFile(IOUtils::getPath<PhongMaterial>(fileName));

   // TODO make reusable somehow
   SPtr<ShaderProgram> shaderProgram = ShaderProgramDeserializer::deserialize(root["shaderProgram"].asString());
   scene->addShaderProgram(shaderProgram);

   // Ambient color
   Json::Value ambientValue = root["ambient"];
   float ambientR = ambientValue["r"].asFloat();
   float ambientG = ambientValue["g"].asFloat();
   float ambientB = ambientValue["b"].asFloat();
   glm::vec3 ambient(ambientR, ambientG, ambientB);

   // Diffuse color
   Json::Value diffuseValue = root["diffuse"];
   float diffuseR = diffuseValue["r"].asFloat();
   float diffuseG = diffuseValue["g"].asFloat();
   float diffuseB = diffuseValue["b"].asFloat();
   glm::vec3 diffuse(diffuseR, diffuseG, diffuseB);

   // Specular color
   Json::Value specularValue = root["specular"];
   float specularR = specularValue["r"].asFloat();
   float specularG = specularValue["g"].asFloat();
   float specularB = specularValue["b"].asFloat();
   glm::vec3 specular(specularR, specularG, specularB);

   // Emission color
   Json::Value emissionValue = root["emission"];
   float emissionR = emissionValue["r"].asFloat();
   float emissionG = emissionValue["g"].asFloat();
   float emissionB = emissionValue["b"].asFloat();
   glm::vec3 emission(emissionR, emissionG, emissionB);

   // Shininess
   float shininess = root["shininess"].asFloat();

   return std::make_shared<PhongMaterial>(fileName, shaderProgram, ambient, diffuse, specular, emission, shininess);
}

} // namespace PhongMaterialDeserializer
