#ifndef PLAIN_TEXTURE_MATERIAL_H
#define PLAIN_TEXTURE_MATERIAL_H

#include "FrameBuffer.h"
#include "GLIncludes.h"
#include "Material.h"

class PlainTextureMaterial : public Material {
protected:
   GLuint texture_id;
   GLint uTexture, aTexCoord;

   const std::string textureFileName;

public:
   static const std::string CLASS_NAME;

   PlainTextureMaterial(const std::string &jsonFileName,
      SPtr<ShaderProgram> shaderProgram, const std::string &textureFileName);

   virtual ~PlainTextureMaterial();

   /**
   * Serializes the object to JSON.
   */
   virtual Json::Value serialize() const;

   virtual void apply(const RenderData &renderData, const Mesh &mesh);

   virtual void disable();
};

#endif
