#ifndef SHADER_H
#define SHADER_H

#include "GLIncludes.h"

#include <memory>
#include <string>

class Shader;
typedef std::shared_ptr<Shader> ShaderRef;

class Shader {
private:
   GLuint id;
   GLenum type;
   std::string fileName;

public:
   Shader(const GLenum type, const std::string &fileName);
   ~Shader();
   void compile();
   GLint getID() const;
};

#endif