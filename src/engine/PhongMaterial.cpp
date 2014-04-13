#include "PhongMaterial.h"

#include <string>

PhongMaterial::PhongMaterial(ShaderProgramRef shaderProgram, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 emission, float shininess)
   : Material(shaderProgram) {
   this->ambient = ambient;
   this->diffuse = diffuse;
   this->specular = specular;
   this->emission = emission;
   this->shininess = shininess;

   uAmbient = shaderProgram->addUniform("uMaterial.ambient");
   uDiffuse = shaderProgram->addUniform("uMaterial.diffuse");
   uSpecular = shaderProgram->addUniform("uMaterial.specular");
   uEmission = shaderProgram->addUniform("uMaterial.emission");
   uShininess = shaderProgram->addUniform("uMaterial.shininess");
}

PhongMaterial::~PhongMaterial() {

}

void PhongMaterial::apply() {
   glUniform3fv(uAmbient, 1, glm::value_ptr(ambient));
   glUniform3fv(uDiffuse, 1, glm::value_ptr(diffuse));
   glUniform3fv(uSpecular, 1, glm::value_ptr(specular));
   glUniform3fv(uEmission, 1, glm::value_ptr(emission));
   glUniform1f(uShininess, shininess);
}