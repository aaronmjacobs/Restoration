#include "FancyAssert.h"
#include "lib/stb_image.h"
#include "Loader.h"
#include "Mesh.h"
#include "PlainTextureMaterial.h"

const std::string PlainTextureMaterial::CLASS_NAME = "PlainTextureMaterial";

PlainTextureMaterial::PlainTextureMaterial(const std::string &jsonFileName,
   SPtr<ShaderProgram> shaderProgram, const std::string &textureFileName)
   : Material(jsonFileName, shaderProgram), textureFileName(textureFileName) {

   uTexture = shaderProgram->getUniform("uTexture");
   aTexCoord = shaderProgram->getAttribute("aTexCoord");

   Loader &loader =  Loader::getInstance();
   texture_id = loader.loadTexture(textureFileName);
}

PlainTextureMaterial::~PlainTextureMaterial() {
}

Json::Value PlainTextureMaterial::serialize() const {
   Json::Value root;

   // Class name
   root["@class"] = CLASS_NAME;

   // Shader program
   root["shaderProgram"] = shaderProgram->getJsonFileName();

   // Texture
   root["texture"] = textureFileName;

   return root;
}

void PlainTextureMaterial::apply(const RenderData &renderData, const Mesh &mesh) {
   shaderProgram->use();

   /* Texture Shading */
   glActiveTexture(GL_TEXTURE0 + texture_id);
   glBindTexture(GL_TEXTURE_2D, texture_id);
   glUniform1i(uTexture, texture_id);
   glEnableVertexAttribArray(aTexCoord);
   glBindBuffer(GL_ARRAY_BUFFER, mesh.getTBO());
   glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void PlainTextureMaterial::disable() {
   glDisableVertexAttribArray(aTexCoord);
}
