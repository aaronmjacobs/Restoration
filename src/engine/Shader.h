#ifndef SHADER_H
#define SHADER_H

#include "GLIncludes.h"

#include <memory>
#include <string>

class Shader;
typedef std::shared_ptr<Shader> ShaderRef;

/**
 * A GLSL shader (vertex / fragment / geometry).
 */
class Shader {
private:
   /**
    * The shader's handle.
    */
   GLuint id;

   /**
    * The type of shader (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, or
    * GL_GEOMETRY_SHADER).
    */
   GLenum type;

   /**
    * The name of the GLSL source file.
    */
   std::string fileName;

public:
   /**
    * Constructs the shader with the given type and source file.
    */
   Shader(const GLenum type, const std::string &fileName);

   /**
    * Deallocates the GL shader.
    */
   virtual ~Shader();

   /**
    * Compiles the shader with the source from the file.
    */
   void compile();

   /**
    * Gets the shader's handle.
    */
   GLuint getID() const {
      return id;
   }
};

#endif
