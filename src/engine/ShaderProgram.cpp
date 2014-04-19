#include "FancyAssert.h"
#include "Shader.h"
#include "ShaderProgram.h"

const std::string ShaderProgram::JSON_FOLDER_PATH = "data/shaderprogram/";

ShaderProgram::ShaderProgram(const std::string &jsonFileName)
 : Serializable(jsonFileName) {
   id = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
   glDeleteProgram(id);
}

Json::Value ShaderProgram::serialize() const {
   Json::Value root;

   // Save the file name of each shader
   Json::Value shadersVal;
   for (ShaderRef shader : shaders) {
      shadersVal.append(shader->getFullJsonPath());
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

void ShaderProgram::attach(ShaderRef shader) {
   glAttachShader(id, shader->getID());
   shaders.push_back(shader);
}

void ShaderProgram::compileShaders() {
   // Compile each attached shader
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
   std::map<std::string, GLint>::iterator it = attributeMap.find(name);
   ASSERT(it != attributeMap.end(), "Unable to find attribute: %s", name.c_str());

   return attributeMap[name];
}

GLint ShaderProgram::getUniform(const std::string &name) {
   // Make sure the uniform exists in the map.
   std::map<std::string, GLint>::iterator it = uniformMap.find(name);
   ASSERT(it != uniformMap.end(), "Unable to find uniform: %s", name.c_str());

   return uniformMap[name];
}
