#ifndef SHADER_H
#define SHADER_H

#include "GLIncludes.h"

#include <string>

class Shader {
private:
   GLuint id;
   GLenum type;
   void compile(const std::string &source);

public:
   Shader(const GLenum type, const std::string &fileName);
   ~Shader();
   GLint getID() const;
};

#endif