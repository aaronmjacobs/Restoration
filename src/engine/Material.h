#ifndef MATERIAL_H
#define MATERIAL_H

#include "ShaderProgram.h"

#include <memory>

class Material;
typedef std::shared_ptr<Material> MaterialRef;

/**
 * Abstract representation of a material (visual properties of geometry).
 */
class Material {
protected:
   /**
    * Shader program with which to draw.
    */
   ShaderProgramRef shaderProgram;

public:
   /**
    * Constructs a material with the given shader program.
    */
   Material(ShaderProgramRef shaderProgram);

   /**
    * Does cleanup (currently nothing!).
    */
   virtual ~Material();

   /**
    * Gets the shader program used by this material.
    */
   ShaderProgramRef getShaderProgram() {
      return shaderProgram;
   }

   /**
    * Applies the properties of the material to the shader.
    */
   virtual void apply() = 0;
};

#endif
