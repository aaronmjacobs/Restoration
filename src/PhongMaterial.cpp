#include "IOUtils.h"
#include "PhongMaterial.h"
#include "RenderState.h"

const std::string PhongMaterial::CLASS_NAME = "PhongMaterial";

PhongMaterial::PhongMaterial(const std::string &jsonFileName, SPtr<ShaderProgram> shaderProgram, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, const glm::vec3 &emission, float shininess)
   : Material(jsonFileName, shaderProgram), ambient(ambient), diffuse(diffuse), specular(specular), emission(emission), shininess(shininess) {
   uAmbient = shaderProgram->getUniform("uMaterial.ambient");
   uDiffuse = shaderProgram->getUniform("uMaterial.diffuse");
   uSpecular = shaderProgram->getUniform("uMaterial.specular");
   uEmission = shaderProgram->getUniform("uMaterial.emission");
   uShininess = shaderProgram->getUniform("uMaterial.shininess");

   uAmbientMap = shaderProgram->getUniform("uAmbientMap");
   uAmbientGlobal = shaderProgram->getUniform("uAmbientGlobal");
}

PhongMaterial::~PhongMaterial() {
}

Json::Value PhongMaterial::serialize() const {
   Json::Value root;

   // Class name
   root["@class"] = CLASS_NAME;

   // Shader program
   root["shaderProgram"] = shaderProgram->getJsonFileName();

   // Ambient color
   Json::Value ambientValue;
   ambientValue["r"] = ambient.r;
   ambientValue["g"] = ambient.g;
   ambientValue["b"] = ambient.b;
   root["ambient"] = ambientValue;

   // Diffuse color
   Json::Value diffuseValue;
   diffuseValue["r"] = diffuse.r;
   diffuseValue["g"] = diffuse.g;
   diffuseValue["b"] = diffuse.b;
   root["diffuse"] = diffuseValue;

   // Specular color
   Json::Value specularValue;
   specularValue["r"] = specular.r;
   specularValue["g"] = specular.g;
   specularValue["b"] = specular.b;
   root["specular"] = specularValue;

   // Emission color
   Json::Value emissionValue;
   emissionValue["r"] = emission.r;
   emissionValue["g"] = emission.g;
   emissionValue["b"] = emission.b;
   root["emission"] = emissionValue;

   // Shininess
   root["shininess"] = shininess;

   return root;
}

void PhongMaterial::apply(const RenderData &renderData, const Mesh &mesh) {
   shaderProgram->use();
   glUniform3fv(uAmbient, 1, glm::value_ptr(ambient));
   glUniform3fv(uDiffuse, 1, glm::value_ptr(diffuse));
   glUniform3fv(uSpecular, 1, glm::value_ptr(specular));
   glm::vec3 selectHighlight = isSelected() ? glm::vec3(0.5f) : glm::vec3(0.0f);
   glUniform3fv(uEmission, 1, glm::value_ptr(emission + selectHighlight));
   glUniform1f(uShininess, shininess);

   if (renderData.getRenderState() & LIGHTWORLD_STATE || renderData.getRenderState() & DARKWORLD_STATE) {
      GLuint ambientMapID = renderData.getGLuint("ambientMapID");
      GLuint ambientGlobalID = renderData.getGLuint("ambientGlobalID");

      glActiveTexture(GL_TEXTURE0 + ambientMapID);
      glBindTexture(GL_TEXTURE_CUBE_MAP, ambientMapID);
      glUniform1i(uAmbientMap, ambientMapID);

      glActiveTexture(GL_TEXTURE0 + ambientGlobalID);
      glBindTexture(GL_TEXTURE_2D, ambientGlobalID);
      glUniform1i(uAmbientGlobal, ambientGlobalID);
   }
}
