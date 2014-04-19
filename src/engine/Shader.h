#ifndef SHADER_H
#define SHADER_H

#include "GLIncludes.h"
#include "Serializable.h"

#include <memory>
#include <string>

class Shader;
typedef std::shared_ptr<Shader> ShaderRef;

/**
 * A GLSL shader (vertex / fragment / geometry).
 */
class Shader : public Serializable {
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
    * Path to the folder that serialized (JSON) files will be stored in.
    */
   static const std::string JSON_FOLDER_PATH;

   /**
    * Constructs the shader with the given type and source file.
    */
   Shader(const std::string &jsonFileName, const GLenum type, const std::string &fileName);

   /**
    * Deallocates the GL shader.
    */
   virtual ~Shader();

   /**
    * Compiles the shader with the source from the file.
    */
   void compile();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

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

   virtual std::string getJsonFolderName() const {
      return JSON_FOLDER_PATH;
   }
};

#endif
