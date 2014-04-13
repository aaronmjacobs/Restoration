#ifndef SHADER_PROG_H
#define SHADER_PROG_H

#include "GLIncludes.h"
#include "Shader.h"

#include <list>
#include <map>
#include <memory>

class ShaderProgram;
typedef std::shared_ptr<ShaderProgram> ShaderProgramRef;

/**
 * All available types of shader attributes.
 */
enum AttributeType { POSITION, NORMAL, TEXTURE };

/**
 * A shader program, composed of at least two shaders.
 */
class ShaderProgram {
private:
   /**
    * The shader program's handle.
    */
   GLuint id;

   /**
    * All shaders attached to the program.
    */
   std::list<ShaderRef> shaders;

   /**
    * A map of attribute names to their locations.
    */
   std::map<std::string, GLint> attributeMap;

   /**
    * A map of uniform names to their location.
    */
   std::map<std::string, GLint> uniformMap;

public:
   /**
    * Constructs a shader program.
    */
   ShaderProgram();

   /**
    * Deallocates the GL shader program.
    */
   virtual ~ShaderProgram();

   /**
    * Attaches the given shader to the program.
    */
   void attach(ShaderRef shader);

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
    * Adds the attribute with the given type and name to the attribute map.
    */
   GLint addAttribute(AttributeType type, const std::string &name);

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
