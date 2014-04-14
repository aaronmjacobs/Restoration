#include "FancyAssert.h"
#include "Material.h"

Material::Material(ShaderProgramRef shaderProgram) {
   ASSERT(shaderProgram, "Null shader program");
   this->shaderProgram = shaderProgram;
}

Material::~Material() {
}
