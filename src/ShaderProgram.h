#ifndef SHADER_PROG_H
#define SHADER_PROG_H

#include "GLIncludes.h"

#include <map>

class Shader;

enum AttributeType { POSITION, NORMAL, TEXTURE };

class ShaderProgram {
private:
   GLuint id;
   GLuint shaderCount;

   std::map<std::string, GLint> attributeMap;
   std::map<std::string, GLint> uniformMap;

public:
   ShaderProgram();
   ~ShaderProgram();
   void attach(const Shader &shader);
   void link();
   void use();
   void disable();
   void loadFields(const std::string &fileName);
   GLint addAttribute(AttributeType type, const std::string &name);
   GLint addUniform(const std::string &name);
   GLint getAttribute(const std::string &name);
   GLint getUniform(const std::string &name);
};

#endif