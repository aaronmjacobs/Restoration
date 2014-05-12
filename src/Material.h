#ifndef MATERIAL_H
#define MATERIAL_H

#include "Saveable.h"
#include "ShaderProgram.h"
#include "Types.h"

class Mesh;

class Material : public Saveable {
protected:
   bool light = false;
   /**
    * Shader program with which to draw.
    */
   SPtr<ShaderProgram> shaderProgram;

public:
   static const std::string CLASS_NAME;
   static const std::string FOLDER_NAME;

   /**
    * Constructs a material with the given shader program.
    */
   Material(const std::string &jsonFileName, SPtr<ShaderProgram> shaderProgram);

   /**
   * Constructs a material with the given shader program. Used for creating material without json file.
   * EX: Render to texture via Frame Buffer Object.
   */
   Material(SPtr<ShaderProgram> shaderProgram);

   /**
    * Does cleanup.
    */
   virtual ~Material();

   void setLight(bool light) {
      this->light = light;
   }

   /**
    * Gets the shader program used by this material.
    */
   SPtr<ShaderProgram> getShaderProgram();

   /**
    * Applies the properties of the material to the shader.
    */
   virtual void apply(SPtr<Mesh> mesh) = 0;
};

#endif
