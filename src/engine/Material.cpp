#include "FancyAssert.h"
#include "Material.h"

const std::string Material::CLASS_NAME = "Material";
const std::string Material::JSON_FOLDER_PATH = "data/material/";

Material::Material(const std::string &jsonFileName, ShaderProgramRef shaderProgram)
   : Serializable(jsonFileName) {
   ASSERT(shaderProgram, "Null shader program");
   this->shaderProgram = shaderProgram;
}

Material::~Material() {
}
