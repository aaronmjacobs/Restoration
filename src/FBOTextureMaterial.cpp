#include "FancyAssert.h"
#include "FBOTextureMaterial.h"
#include "lib/stb_image.h"
#include "Mesh.h"

const std::string FBOTextureMaterial::CLASS_NAME = "FBOTextureMaterial";

FBOTextureMaterial::FBOTextureMaterial(const std::string &jsonFileName,
   SPtr<ShaderProgram> shaderProgram, FrameBuffer &fb) : Material(jsonFileName, shaderProgram) {

   texture_id = fb.getTextureID();
   uTexture = shaderProgram->getUniform("uTexture");
   aTexCoord = shaderProgram->getAttribute("aTexCoord");
}

FBOTextureMaterial::~FBOTextureMaterial() {
}

void FBOTextureMaterial::apply(const RenderData &renderData, const Mesh &mesh) {
   shaderProgram->use();

   /* Texture Shading */
   glEnable(GL_TEXTURE_2D);
   glActiveTexture(GL_TEXTURE0 + texture_id);
   glBindTexture(GL_TEXTURE_2D, texture_id);

   glUniform1i(uTexture, texture_id);

   glEnableVertexAttribArray(aTexCoord);
   glBindBuffer(GL_ARRAY_BUFFER, mesh.getTBO());
   glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

Json::Value FBOTextureMaterial::serialize() const {
   Json::Value root;

   // Class name
   root["@class"] = CLASS_NAME;

   // Shader program
   root["shaderProgram"] = shaderProgram->getJsonFileName();

   return root;
}
