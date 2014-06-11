#include "FancyAssert.h"
#include "FBOTextureMaterial.h"
#include "lib/stb_image.h"
#include "Mesh.h"
#include "TextureUnitManager.h"

const std::string FBOTextureMaterial::CLASS_NAME = "FBOTextureMaterial";

FBOTextureMaterial::FBOTextureMaterial(const std::string &jsonFileName,
   SPtr<ShaderProgram> shaderProgram, FrameBuffer &fb) : Material(jsonFileName, shaderProgram) {

   texture_id = fb.getTextureID();
   uTexture = shaderProgram->getUniform("uTexture");
   aTexCoord = shaderProgram->getAttribute("aTexCoord");
}

FBOTextureMaterial::FBOTextureMaterial(const std::string &jsonFileName,
   SPtr<ShaderProgram> shaderProgram, Shadow &fb) : Material(jsonFileName, shaderProgram) {

   texture_id = fb.getTextureID();
   uTexture = shaderProgram->getUniform("uTexture");
   aTexCoord = shaderProgram->getAttribute("aTexCoord");
}

FBOTextureMaterial::~FBOTextureMaterial() {
}

Json::Value FBOTextureMaterial::serialize() const {
   Json::Value root;

   // Class name
   root["@class"] = CLASS_NAME;

   // Shader program
   root["shaderProgram"] = shaderProgram->getJsonFileName();

   return root;
}

void FBOTextureMaterial::apply(const RenderData &renderData, const Mesh &mesh) {
   shaderProgram->use();

   /* Texture Shading */
   GLenum textureUnit = TextureUnitManager::get();
   glActiveTexture(GL_TEXTURE0 + textureUnit);
   glBindTexture(GL_TEXTURE_2D, texture_id); // renderData.getGLuint("sh")

   glUniform1i(uTexture, textureUnit);

   glEnableVertexAttribArray(aTexCoord);
   glBindBuffer(GL_ARRAY_BUFFER, mesh.getTBO());
   glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void FBOTextureMaterial::disable() {
   glDisableVertexAttribArray(aTexCoord);
   TextureUnitManager::release();
   shaderProgram->disable();
}
