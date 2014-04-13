#ifndef PHONG_MATERIAL_H
#define PHONG_MATERIAL_H

#include "Material.h"

#include "GLMIncludes.h"

class PhongMaterial : public Material {
private:
   glm::vec3 ambient, diffuse, specular, emission;
   float shininess;
   GLint uAmbient, uDiffuse, uSpecular, uEmission, uShininess;

public:
   PhongMaterial(ShaderProgramRef shaderProgram, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 emission, float shininess);
   virtual ~PhongMaterial();
   virtual void apply();
};

#endif