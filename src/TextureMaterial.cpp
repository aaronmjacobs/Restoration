#include "FancyAssert.h"
#include "Loader.h"
#include "Mesh.h"
#include "RenderState.h"
#include "TextureMaterial.h"

const std::string TextureMaterial::CLASS_NAME = "TextureMaterial";

TextureMaterial::TextureMaterial(const std::string &jsonFileName,
                   SPtr<ShaderProgram> shaderProgram,
                   const glm::vec3 &ambient,
                   const glm::vec3 &diffuse,
                   const glm::vec3 &specular,
                   const glm::vec3 &emission,
                   float shininess,
                   const std::string &textureFileName)
   : PhongMaterial(jsonFileName, shaderProgram, ambient, diffuse, specular, emission, shininess), textureFileName(textureFileName) {
   
   // Generate Texture ID, get the attribute and uniforms for texture.
   uTexture = shaderProgram->getUniform("uTexture");
   uAmbientMap = shaderProgram->getUniform("uAmbientMap");
   uAmbientGlobal = shaderProgram->getUniform("uAmbientGlobal");
   aTexCoord = shaderProgram->getAttribute("aTexCoord");

   SPtr<Loader> loader = Loader::getInstance();
   textureID = loader->loadTexture(textureFileName);
}

TextureMaterial::~TextureMaterial() {
   glDeleteTextures(1, &textureID);
}

Json::Value TextureMaterial::serialize() const {
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

   // Texture
   root["texture"] = textureFileName;
   return root;
}

/* Current functionality for single texture only. Not multitexturing. */
void TextureMaterial::apply(const RenderData &renderData, const Mesh &mesh){
   shaderProgram->use();

   /* Texture Shading */
   glEnable(GL_TEXTURE_2D);
   glActiveTexture(GL_TEXTURE0 + textureID);
   glBindTexture(GL_TEXTURE_2D, textureID);
   glUniform1i(uTexture, textureID);
   glEnableVertexAttribArray(aTexCoord);
   glBindBuffer(GL_ARRAY_BUFFER, mesh.getTBO());
   glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

   // TODO
   ambient = glm::vec3(0.35, 0.41, 0.47);
   if (renderData.getRenderState() & DARKWORLD_STATE) {
      ambient = glm::vec3(0.42, 0.35, 0.28);
   }

   /* Phong Shading */
   glUniform3fv(uAmbient, 1, glm::value_ptr(ambient));
   glUniform3fv(uDiffuse, 1, glm::value_ptr(diffuse));
   glUniform3fv(uSpecular, 1, glm::value_ptr(specular));
   glUniform3fv(uEmission, 1, glm::value_ptr(emission));
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

void TextureMaterial::disable(){
   glDisableVertexAttribArray(shaderProgram->getAttribute("aPosition"));
   glDisableVertexAttribArray(shaderProgram->getAttribute("aNormal"));
   glDisableVertexAttribArray(shaderProgram->getAttribute("aTexCoord"));
   glDisable(GL_TEXTURE_2D);
}