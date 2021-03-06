#ifndef TEXTURE_MATERIAL_H
#define TEXTURE_MATERIAL_H

#include "PhongMaterial.h"
#include "FrameBuffer.h"

class TextureMaterial : public PhongMaterial {
protected:
   GLuint textureID, altTextureID;
   GLint uTexture, aTexCoord;

   const std::string textureFileName;
   const std::string altTextureFileName;

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
                   const std::string &textureFileName,
                   const std::string &altTextureFileName = "");

   /**
    * Delete the texture.
    */
   virtual ~TextureMaterial();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   virtual void apply(const RenderData &renderData, const Mesh &mesh);

   virtual void disable();

   bool hasAltTexture();
};

#endif
