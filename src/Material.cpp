#include "Material.h"

Material::Material(ShaderProgramRef shaderProgram) {
   this->shaderProgram = shaderProgram;
}

Material::~Material() {

}

void Material::apply() {
   shaderProgram->use();
   // TODO glUniform calls
}