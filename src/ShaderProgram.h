#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "GLIncludes.h"
#include "Saveable.h"
#include "Types.h"

#include <list>
#include <map>

class Shader;

class ShaderProgram : public Saveable {
protected:
   /**
    * The shader program's handle.
    */
   GLuint id;

   /**
    * All shaders attached to the program.
    */
   std::list<SPtr<Shader>> shaders;

   /**
    * A map of attribute names to their locations.
    */
   std::map<std::string, GLint> attributeMap;

   /**
    * A map of uniform names to their location.
    */
   std::map<std::string, GLint> uniformMap;

public:
   static const std::string CLASS_NAME;
   static const std::string FOLDER_NAME;

   /**
    * Constructs a shader program.
    */
   ShaderProgram(const std::string &jsonFileName);

   /**
    * Deallocates the GL shader program.
    */
   virtual ~ShaderProgram();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   /**
    * Gets the name of the folder the serializable will be written to.
    */
   virtual std::string getJsonFolderName() const {
      return FOLDER_NAME;
   }

   /**
    * Attaches the given shader to the program.
    */
   void attach(SPtr<Shader> shader);

   /**
    * Compiles all attached shaders (loading source from the GLSL files).
    */
   void compileShaders();

   /**
    * Links the shader program.
    */
   void link();

   /**
    * Sets the program as the active program.
    */
   void use();

   /**
    * Disables the program.
    */
   void disable();

   /**
    * Adds the attribute with the given name to the attribute map.
    */
   GLint addAttribute(const std::string &name);

   /**
    * Adds the uniform with the given name to the uniform map.
    */
   GLint addUniform(const std::string &name);

   /**
    * Gets the location of the attribute with the given name from the attribute
    * map.
    */
   GLint getAttribute(const std::string &name);

   /**
    * Gets the location of the uniform with the given name from the uniform map.
    */
   GLint getUniform(const std::string &name);
};

#endif
