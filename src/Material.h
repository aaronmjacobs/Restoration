#ifndef MATERIAL_H
#define MATERIAL_H

#include "ShaderProgram.h"

#include <memory>

class Material;
typedef std::shared_ptr<Material> MaterialRef;

class Material {
protected:
   ShaderProgramRef shaderProgram;

public:
   Material(ShaderProgramRef shaderProgram);
   ShaderProgramRef getShaderProgram() {
      return shaderProgram;
   }
   virtual ~Material();
   virtual void apply();
};

#endif