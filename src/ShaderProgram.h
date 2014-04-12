#ifndef SHADER_PROG_H
#define SHADER_PROG_H

#include "GLIncludes.h"
#include "Shader.h"

#include <list>
#include <map>
#include <memory>

class ShaderProgram;

typedef std::shared_ptr<ShaderProgram> ShaderProgramRef;

enum AttributeType { POSITION, NORMAL, TEXTURE };

class ShaderProgram {
private:
   GLuint id;

   std::list<ShaderRef> shaders;
   std::map<std::string, GLint> attributeMap;
   std::map<std::string, GLint> uniformMap;

public:
   ShaderProgram();
   ~ShaderProgram();
   void attach(ShaderRef shader);
   void compileShaders();
   void link();
   void use();
   void disable();
   GLint addAttribute(AttributeType type, const std::string &name);
   GLint addUniform(const std::string &name);
   GLint getAttribute(const std::string &name);
   GLint getUniform(const std::string &name);
};

#endif