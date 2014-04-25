#include "engine/fancyAssert.h"
#include "engine/lib/stb_image.h"
#include "TextureMaterial.h"

const std::string TextureMaterial::CLASS_NAME = "TextureMaterial";

TextureMaterial::TextureMaterial(const std::string &jsonFileName, ShaderProgramRef shaderProgram,
   glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 emission,
   float shininess, const std::string &textureFileName) : PhongMaterial(jsonFileName, shaderProgram,
   ambient, diffuse, specular, emission, shininess), textureFile(textureFileName) {
   
   // Generate Texture ID, get the attribute and uniforms for texture.
   glGenTextures(1, &(texture_id));
   uTexture = shaderProgram->getUniform("uTexture");
   aTexCoord = shaderProgram->getAttribute("aTexCoord");
   std::cerr << "I should be getting here\n";
   this->CreateTexture();
}

TextureMaterial::~TextureMaterial() {
   glDeleteTextures(1, &(texture_id));
   stbi_image_free(data);
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
   root["texture"] = textureFile;
   return root;
}

void TextureMaterial::CreateTexture(){
   glGenTextures(1, &(texture_id));
   glBindTexture(GL_TEXTURE_2D, texture_id);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   
   // Call the stb_image function for width, height, data.
   FILE *file = fopen(textureFile.c_str(), "rb");
   ASSERT(file, "Null file");
   data = stbi_load_from_file(file, &(x), &(y), &(comp), 0);
   fclose(file);
   std::cerr << comp << "\n";
   if (comp == 4)
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   else if (comp == 3)
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
   else{
      stbi_image_free(data);
      ASSERT(NULL, "composition of image is not 3 or 4");
   }
   
      
}

/* Current functionality for single texture only. Not multitexturing. */
void TextureMaterial::apply(){
   shaderProgram->use();

   /* Texture Shading */
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, texture_id);
   glUniform1i(uTexture, /*GL_TEXTURE*/0);
   glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

   /* Phong Shading */
   glUniform3fv(uAmbient, 1, glm::value_ptr(ambient));
   glUniform3fv(uDiffuse, 1, glm::value_ptr(diffuse));
   glUniform3fv(uSpecular, 1, glm::value_ptr(specular));
   glUniform3fv(uEmission, 1, glm::value_ptr(emission));
   glUniform1f(uShininess, shininess);
}
