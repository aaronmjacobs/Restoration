#ifndef TEXTURE_MATERIAL_H
#define TEXTURE_MATERIAL_H

#include "PhongMaterial.h"

class TextureMaterial : public PhongMaterial {
private:
   void createTexture();

protected:
   GLuint texture_id;
   GLint uTexture, aTexCoord;

   const std::string textureFileName;

public:
   /**
    * Name of the class (used in deserialization to determine types).
    */
   static const std::string CLASS_NAME;

   /**
    * Create the texture id and phong material
    */
   TextureMaterial(const std::string &jsonFileName,
                   SPtr<ShaderProgram> shaderProgram,
                   const glm::vec3 &ambient,
                   const glm::vec3 &diffuse,
                   const glm::vec3 &specular,
                   const glm::vec3 &emission,
                   float shininess,
                   const std::string &textureFileName);

   /**
    * Delete the texture.
    */
   virtual ~TextureMaterial();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   virtual void apply(SPtr<Mesh> mesh);

   virtual void disable();
};

#endif
