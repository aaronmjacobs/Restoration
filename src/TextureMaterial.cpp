#include "FancyAssert.h"
#include "lib/stb_image.h"
#include "Mesh.h"
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
   aTexCoord = shaderProgram->getAttribute("aTexCoord");
   createTexture();
}

TextureMaterial::TextureMaterial(SPtr<FrameBuffer> frameBuffer,
                   SPtr<ShaderProgram> shaderProgram,
                   const glm::vec3 &ambient,
                   const glm::vec3 &diffuse,
                   const glm::vec3 &specular,
                   const glm::vec3 &emission,
                   float shininess)
   : PhongMaterial(shaderProgram, ambient, diffuse, specular, emission, shininess){
   uTexture = shaderProgram->getUniform("uTexture");
   aTexCoord = shaderProgram->getAttribute("aTexCoord");
   texture_id = frameBuffer->getTextureID();
}

TextureMaterial::~TextureMaterial() {
   glDeleteTextures(1, &texture_id);
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

void TextureMaterial::createTexture(){
   glGenTextures(1, &texture_id);
   glBindTexture(GL_TEXTURE_2D, texture_id);

   int x, y, comp;

   // Call the stb_image function for width, height, data.
   FILE *file = fopen(textureFileName.c_str(), "rb");
   ASSERT(file, "Unable to open file: %s", textureFileName.c_str());
   unsigned char *data = stbi_load_from_file(file, &x, &y, &comp, 0);
   fclose(file);

   if (comp == 4) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   } else if (comp == 3) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
   } else {
      ASSERT(false, "composition of image is not 3 or 4");
   }

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glBindTexture(GL_TEXTURE_2D, 0);

   stbi_image_free(data);
}

/* Current functionality for single texture only. Not multitexturing. */
void TextureMaterial::apply(SPtr<Mesh> mesh){
   shaderProgram->use();

   /* Texture Shading */
   glEnable(GL_TEXTURE_2D);
   glActiveTexture(GL_TEXTURE0 + texture_id);
   glBindTexture(GL_TEXTURE_2D, texture_id);
   glUniform1i(uTexture, texture_id);
   glEnableVertexAttribArray(aTexCoord);
   glBindBuffer(GL_ARRAY_BUFFER, mesh->getTBO());
   glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

   /* Phong Shading */
   glUniform3fv(uAmbient, 1, glm::value_ptr(ambient));
   glUniform3fv(uDiffuse, 1, glm::value_ptr(diffuse));
   glUniform3fv(uSpecular, 1, glm::value_ptr(specular));
   glUniform3fv(uEmission, 1, glm::value_ptr(emission));
   glUniform1f(uShininess, shininess);
}

void TextureMaterial::disable(){
   glDisableVertexAttribArray(shaderProgram->getAttribute("aPosition"));
   glDisableVertexAttribArray(shaderProgram->getAttribute("aNormal"));
   glDisableVertexAttribArray(shaderProgram->getAttribute("aTexCoord"));
   glDisable(GL_TEXTURE_2D);
}