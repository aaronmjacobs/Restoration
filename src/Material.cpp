#include "FancyAssert.h"
#include "Material.h"

const std::string Material::CLASS_NAME = "Material";
const std::string Material::FOLDER_NAME = "materials";

Material::Material(const std::string &jsonFileName, SPtr<ShaderProgram> shaderProgram)
   : Saveable(jsonFileName) {
   ASSERT(shaderProgram, "Null shader program");
   this->shaderProgram = shaderProgram;
}

Material::~Material() {
}

SPtr<ShaderProgram> Material::getShaderProgram() {
   return shaderProgram;
}
