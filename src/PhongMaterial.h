#ifndef PHONG_MATERIAL_H
#define PHONG_MATERIAL_H

#include "GLIncludes.h"
#include "GLMIncludes.h"
#include "Material.h"

class PhongMaterial : public Material {
protected:
   glm::vec3 ambient, diffuse, specular, emission;
   float shininess;
   GLint uAmbient, uDiffuse, uSpecular, uEmission, uShininess, uAmbientMap, uAmbientGlobal;

public:
   static const std::string CLASS_NAME;

   PhongMaterial(const std::string &jsonFileName,
                 SPtr<ShaderProgram> shaderProgram,
                 const glm::vec3 &ambient,
                 const glm::vec3 &diffuse,
                 const glm::vec3 &specular,
                 const glm::vec3 &emission,
                 float shininess);

   virtual ~PhongMaterial();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   virtual void apply(const RenderData &renderData, const Mesh &mesh);
};

#endif
