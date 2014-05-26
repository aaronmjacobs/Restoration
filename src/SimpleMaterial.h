#ifndef SIMPLE_MATERIAL_H
#define SIMPLE_MATERIAL_H

#include "Material.h"

class SimpleMaterial : public Material {
public:
   static const std::string CLASS_NAME;

   SimpleMaterial(const std::string &jsonFileName,
                 SPtr<ShaderProgram> shaderProgram);

   virtual ~SimpleMaterial();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   virtual void apply(const RenderData &renderData, const Mesh &mesh);

   virtual void disable();
};

#endif
