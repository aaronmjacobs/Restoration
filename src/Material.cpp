#include "Material.h"

Material::Material(ShaderProgramRef shaderProgram) {
   this->shaderProgram = shaderProgram;
}

Material::~Material() {

}

void Material::apply() {
   // TODO glUniform calls
}