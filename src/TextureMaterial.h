#ifndef TEXTURE_MATERIAL_H
#define TEXTURE_MATERIAL_H

#include "PhongMaterial.h"
#include <memory>

class TextureMaterial;
typedef std::shared_ptr<TextureMaterial> TextureMaterialRef;

class TextureMaterial : public PhongMaterial {
private:
   void CreateTexture();

protected:
   GLuint texture_id;
   GLint uTexture, aTexCoord;
   int x, y, comp;
   unsigned char *data;

   std::string textureFile;

public:
   /**
   * Name of the class (used in deserialization to determine types).
   */
   static const std::string CLASS_NAME;

   /**
   * Create the texture id and phong material
   */
   TextureMaterial(const std::string &jsonFileName, ShaderProgramRef shaderProgram,
      glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 emission, 
      float shininess, const std::string &textureFileName);

   /**
   * Delete the texture.
   */
   virtual ~TextureMaterial();

   /**
   * Serializes the object to JSON.
   */
   virtual Json::Value serialize() const;

   virtual void apply(MeshRef mesh);

   virtual void disable();
};
#endif