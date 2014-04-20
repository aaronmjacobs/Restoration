#ifndef PHONG_MATERIAL_H
#define PHONG_MATERIAL_H

#include "engine/GLMIncludes.h"
#include "engine/Material.h"

#include <memory>

class PhongMaterial;
typedef std::shared_ptr<PhongMaterial> PhongMaterialRef;

class PhongMaterial : public Material {
private:
   glm::vec3 ambient, diffuse, specular, emission;
   float shininess;
   GLint uAmbient, uDiffuse, uSpecular, uEmission, uShininess;

public:
   /**
    * Name of the class (used in deserialization to determine types).
    */
   static const std::string CLASS_NAME;

   PhongMaterial(const std::string &jsonFileName, ShaderProgramRef shaderProgram, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 emission, float shininess);
   virtual ~PhongMaterial();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;
   virtual void apply();
};

#endif