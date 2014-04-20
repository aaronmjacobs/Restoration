#ifndef MATERIAL_H
#define MATERIAL_H

#include "Serializable.h"
#include "ShaderProgram.h"

#include <memory>

class Material;
typedef std::shared_ptr<Material> MaterialRef;

/**
 * Abstract representation of a material (visual properties of geometry).
 */
class Material : public Serializable {
protected:
   /**
    * Shader program with which to draw.
    */
   ShaderProgramRef shaderProgram;

public:
   /**
    * Name of the class (used in deserialization to determine types).
    */
   static const std::string CLASS_NAME;

   /**
    * Path to the folder that serialized (JSON) files will be stored in.
    */
   static const std::string JSON_FOLDER_PATH;

   /**
    * Constructs a material with the given shader program.
    */
   Material(const std::string &jsonFileName, ShaderProgramRef shaderProgram);

   /**
    * Does cleanup (currently nothing!).
    */
   virtual ~Material();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const = 0;

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

   virtual std::string getJsonFolderName() const {
      return JSON_FOLDER_PATH;
   }
};

#endif
