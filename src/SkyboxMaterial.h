#ifndef SKYBOX_MATERIAL_H
#define SKYBOX_MATERIAL_H

#include "Material.h"

class Camera;

class SkyboxMaterial : public Material {
protected:
   WPtr<Camera> camera;
   GLint aPosition;

public:
   static const std::string CLASS_NAME;

   SkyboxMaterial(const std::string &jsonName,
                  SPtr<ShaderProgram> shaderProgram,
                  SPtr<Camera> camera);

   virtual ~SkyboxMaterial();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   virtual void apply(const RenderData &renderData, const Mesh &mesh);

   virtual void disable();
};

#endif
