#include "FancyAssert.h"

#include "ShaderProgram.h"
#include "Shader.h"

ShaderProgram::ShaderProgram() {
   id = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
   glDeleteProgram(id);
}

void ShaderProgram::attach(ShaderRef shader) {
   glAttachShader(id, shader->getID());
   shaders.push_back(shader);
}

void ShaderProgram::compileShaders() {
   for (ShaderRef shader : shaders) {
      shader->compile();
   }
}

void ShaderProgram::link() {
   ASSERT(shaders.size() >= 2, "Need at least two shaders to link: %lu", shaders.size());

   glLinkProgram(id);

   // Check the status
   GLint linkStatus;
   glGetProgramiv(id, GL_LINK_STATUS, &linkStatus);
   ASSERT(linkStatus == GL_TRUE, "Shader linking failed");
}

void ShaderProgram::use() {
   glUseProgram(id);
}

void ShaderProgram::disable() {
   glUseProgram(0);
}

GLint ShaderProgram::addAttribute(AttributeType type, const std::string &name) {
   attributeMap[name] = type;
   return type;
}

GLint ShaderProgram::addUniform(const std::string &name) {
   const char *nameStr = name.c_str();
   GLint location = glGetUniformLocation(id, nameStr);
   ASSERT(location != -1, "Unable to get uniform location: %s", nameStr);

   uniformMap[name] = location;
   return location;
}

GLint ShaderProgram::getAttribute(const std::string &name) {
   std::map<std::string, GLint>::iterator it = attributeMap.find(name);
   ASSERT(it != attributeMap.end(), "Unable to find attribute: %s", name.c_str());
   return attributeMap[name];
}

GLint ShaderProgram::getUniform(const std::string &name) {
   std::map<std::string, GLint>::iterator it = uniformMap.find(name);
   ASSERT(it != uniformMap.end(), "Unable to find uniform: %s", name.c_str());
   return uniformMap[name];
}
