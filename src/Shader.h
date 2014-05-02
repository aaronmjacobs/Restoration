#ifndef SHADER_H
#define SHADER_H

#include "GLIncludes.h"
#include "Serializable.h"

class Shader : public Serializable {
protected:
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
   static const std::string CLASS_NAME;

   /**
    * Constructs the shader with the given type and source file.
    */
   Shader(const GLenum type, const std::string &fileName);

   /**
    * Deallocates the GL shader.
    */
   virtual ~Shader();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

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

   /**
    * Gets the file name of the shader.
    */
   std::string getFileName() const {
      return fileName;
   };
};

#endif
