#include "PhongMaterialSerializer.h"
#include "Serializer.h"
#include "../engine/IOUtils.h"

#include <memory>

namespace PhongMaterialSerializer {

PhongMaterialRef load(const std::string &jsonFileName) {
   Json::Value root = IOUtils::readJsonFile(Material::JSON_FOLDER_PATH + jsonFileName);

   Serializer::check(root, "shaderProgram", "PhongMaterial");
   std::string shaderProgramJsonFileName = root["shaderProgram"].asString();

   // TODO make reusable somehow
   ShaderProgramRef shaderProgram = ShaderProgramSerializer::load(shaderProgramJsonFileName);

   // Ambient color
   Serializer::check(root, "ambient", "PhongMaterial");
   Json::Value ambientValue = root["ambient"];
   float ambientR = ambientValue["r"].asFloat();
   float ambientG = ambientValue["g"].asFloat();
   float ambientB = ambientValue["b"].asFloat();
   glm::vec3 ambient(ambientR, ambientG, ambientB);

   // Diffuse color
   Serializer::check(root, "diffuse", "PhongMaterial");
   Json::Value diffuseValue = root["diffuse"];
   float diffuseR = diffuseValue["r"].asFloat();
   float diffuseG = diffuseValue["g"].asFloat();
   float diffuseB = diffuseValue["b"].asFloat();
   glm::vec3 diffuse(diffuseR, diffuseG, diffuseB);

   // Specular color
   Serializer::check(root, "specular", "PhongMaterial");
   Json::Value specularValue = root["specular"];
   float specularR = specularValue["r"].asFloat();
   float specularG = specularValue["g"].asFloat();
   float specularB = specularValue["b"].asFloat();
   glm::vec3 specular(specularR, specularG, specularB);

   // Emission color
   Serializer::check(root, "emission", "PhongMaterial");
   Json::Value emissionValue = root["emission"];
   float emissionR = emissionValue["r"].asFloat();
   float emissionG = emissionValue["g"].asFloat();
   float emissionB = emissionValue["b"].asFloat();
   glm::vec3 emission(emissionR, emissionG, emissionB);

   // Shininess
   Serializer::check(root, "shininess", "PhongMaterial");
   float shininess = root["shininess"].asFloat();

   return std::make_shared<PhongMaterial>(jsonFileName, shaderProgram, ambient, diffuse, specular, emission, shininess);
}

} // namespace PhongMaterialSerializer
