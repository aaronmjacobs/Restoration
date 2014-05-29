#include "FancyAssert.h"
#include "Loader.h"
#include "Mesh.h"
#include "RenderState.h"
#include "TextureMaterial.h"
#include "TextureUnitManager.h"

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
   aTexCoord = shaderProgram->getAttribute("aTexCoord");

   Loader& loader = Loader::getInstance();
   textureID = loader.loadTexture(textureFileName);
}

TextureMaterial::~TextureMaterial() {
   // No need to delete the textureID, as it is owned by the loader instance
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
void TextureMaterial::apply(const RenderData &renderData, const Mesh &mesh) {
   PhongMaterial::apply(renderData, mesh);

   /* Texture Shading */
   GLenum textureUnit = TextureUnitManager::get();
   glActiveTexture(GL_TEXTURE0 + textureUnit);
   glBindTexture(GL_TEXTURE_2D, textureID);
   glUniform1i(uTexture, textureUnit);
   glEnableVertexAttribArray(aTexCoord);
   glBindBuffer(GL_ARRAY_BUFFER, mesh.getTBO());
   glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void TextureMaterial::disable(){
   glDisableVertexAttribArray(shaderProgram->getAttribute("aPosition"));
   glDisableVertexAttribArray(shaderProgram->getAttribute("aNormal"));
   glDisableVertexAttribArray(shaderProgram->getAttribute("aTexCoord"));

   TextureUnitManager::release();

   PhongMaterial::disable();
}