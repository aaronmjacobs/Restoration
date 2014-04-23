#include "TextureMaterial.h"

const std::string TextureMaterial::CLASS_NAME = "TextureMaterial";

TextureMaterial::TextureMaterial(const std::string &jsonFileName, ShaderProgramRef shaderProgram,
   glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 emission,
   float shininess, const std::string &textureFileName) : PhongMaterial(jsonFileName, shaderProgram,
   ambient, diffuse, specular, emission, shininess), textureFile(textureFileName) {
   
   glGenTextures(1, &(this->texture_id));
   this->uTexture = shaderProgram->getUniform("uTexture");
}

TextureMaterial::~TextureMaterial() {
   glDeleteTextures(1, &(this->texture_id));
}

void TextureMaterial::CreateTexture(){
   glGenTextures(1, &(this->texture_id));
   glBindTexture(GL_TEXTURE_2D, this->texture_id);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   // Call the stb_image function for width, height, data
   /*
   glTexImage2D(GL_TEXTURE_2D, // target
      0,  // level, 0 = base, no minimap,
      GL_RGB, // internalformat
      512,  // width
      512,  // height
      0,  // border, always 0 in OpenGL ES
      GL_RGB,  // format
      GL_UNSIGNED_BYTE, // type
      pixel_data); //data of image
      */
}

/* Current functionality for single texture only. Not multitexturing. */
void TextureMaterial::apply(){
   shaderProgram->use();

   /* Texture Shading */
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, this->texture_id);
   glUniform1i(uTexture, /*GL_TEXTURE*/0); 

   /* Phong Shading */
   glUniform3fv(uAmbient, 1, glm::value_ptr(ambient));
   glUniform3fv(uDiffuse, 1, glm::value_ptr(diffuse));
   glUniform3fv(uSpecular, 1, glm::value_ptr(specular));
   glUniform3fv(uEmission, 1, glm::value_ptr(emission));
   glUniform1f(uShininess, shininess);
}
