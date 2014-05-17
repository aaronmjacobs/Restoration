#ifndef MATERIAL_H
#define MATERIAL_H

#include "RenderData.h"
#include "Saveable.h"
#include "ShaderProgram.h"
#include "Types.h"

class Mesh;

class Material : public Saveable {
protected:
   /**
    * Shader program with which to draw.
    */
   SPtr<ShaderProgram> shaderProgram;

   bool selected;

public:
   static const std::string CLASS_NAME;
   static const std::string FOLDER_NAME;

   /**
    * Constructs a material with the given shader program.
    */
   Material(const std::string &jsonFileName, SPtr<ShaderProgram> shaderProgram);

   /**
    * Does cleanup.
    */
   virtual ~Material();

   /**
    * Gets the shader program used by this material.
    */
   SPtr<ShaderProgram> getShaderProgram();

   bool isSelected() {
      return selected;
   }

   void setSelected(bool selected) {
      this->selected = selected;
   }

   /**
    * Applies the properties of the material to the shader.
    */
   virtual void apply(const RenderData &renderData, const Mesh &mesh) = 0;
};

#endif
