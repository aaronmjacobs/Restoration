#include "FancyAssert.h"
#include "Shader.h"
#include "ShaderProgram.h"

const std::string ShaderProgram::CLASS_NAME = "ShaderProgram";
const std::string ShaderProgram::FOLDER_NAME = "shader_programs";

ShaderProgram::ShaderProgram(const std::string &jsonFileName)
   : Saveable(jsonFileName) {
   id = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
   glDeleteProgram(id);
}

Json::Value ShaderProgram::serialize() const {
   Json::Value root;

   // Class name
   root["@class"] = CLASS_NAME;

   // Save the file name of each shader
   Json::Value shadersVal;
   for (SPtr<Shader> shader : shaders) {
      shadersVal.append(shader->serialize());
   }
   root["shaders"] = shadersVal;

   // Save the name of each attribute
   Json::Value attribsVal;
   for (std::pair<const std::string, GLint> attribute : attributeMap) {
      attribsVal.append(attribute.first);
   }
   root["attributes"] = attribsVal;

   // Save the name of each uniform
   Json::Value uniformsVal;
   for (std::pair<const std::string, GLint> uniform : uniformMap) {
      uniformsVal.append(uniform.first);
   }
   root["uniforms"] = uniformsVal;

   return root;
}

void ShaderProgram::attach(SPtr<Shader> shader) {
   glAttachShader(id, shader->getID());
   shaders.push_back(shader);
}

void ShaderProgram::compileShaders() {
   // Compile each attached shader
   for (SPtr<Shader> shader : shaders) {
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

GLint ShaderProgram::addAttribute(const std::string &name) {
   const char *nameStr = name.c_str();
   GLint location = glGetAttribLocation(id, nameStr);
   ASSERT(location != -1, "Unable to get attribute location: %s", nameStr);

   attributeMap[name] = location;
   return location;
}

GLint ShaderProgram::addUniform(const std::string &name) {
   const char *nameStr = name.c_str();
   GLint location = glGetUniformLocation(id, nameStr);
   ASSERT(location != -1, "Unable to get uniform location: %s", nameStr);

   uniformMap[name] = location;
   return location;
}

GLint ShaderProgram::getAttribute(const std::string &name) {
   // Make sure the attribute exists in the map
   ASSERT(hasAttribute(name), "Unable to find attribute: %s", name.c_str());

   return attributeMap[name];
}

GLint ShaderProgram::getUniform(const std::string &name) {
   // Make sure the uniform exists in the map.
   ASSERT(hasUniform(name), "Unable to find uniform: %s", name.c_str());

   return uniformMap[name];
}

bool ShaderProgram::hasAttribute(const std::string &name) {
   return attributeMap.count(name) > 0;
}

bool ShaderProgram::hasUniform(const std::string &name) {
   return uniformMap.count(name) > 0;
}
