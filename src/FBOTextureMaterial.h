#ifndef FBO_TEXTURE_MATERIAL_H
#define FBO_TEXTURE_MATERIAL_H

#include "FrameBuffer.h"
#include "GLIncludes.h"
#include "Material.h"

class FBOTextureMaterial : public Material {
protected:
   GLuint texture_id;
   GLint uTexture, aTexCoord;

public:
   static const std::string CLASS_NAME;

   FBOTextureMaterial(const std::string &jsonFileName,
      SPtr<ShaderProgram> shaderProgram, FrameBuffer &fb);

   virtual ~FBOTextureMaterial();

   /**
   * Serializes the object to JSON.
   */
   virtual Json::Value serialize() const;

   virtual void apply(const RenderData &renderData, const Mesh &mesh);

   virtual void disable();
};

#endif
