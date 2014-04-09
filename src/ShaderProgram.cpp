#include "FancyAssert.h"

#include "ShaderProgram.h"
#include "Shader.h"

ShaderProgram::ShaderProgram() {
   id = glCreateProgram();
   shaderCount = 0;
}

ShaderProgram::~ShaderProgram() {
   glDeleteProgram(id);
}

void ShaderProgram::attach(const Shader &shader) {
   glAttachShader(id, shader.getID());
   ++shaderCount;
}

void ShaderProgram::link() {
   ASSERT(shaderCount >= 2, "Need at least two shaders to link: %d", shaderCount);

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

void ShaderProgram::loadFields(const std::string &fileName) {
   // TODO Load fields via JSON
   GLint uModelMatrix = addUniform("uModelMatrix");
   GLint uViewMatrix = addUniform("uViewMatrix");
   GLint uProjMatrix = addUniform("uProjMatrix");
   GLint uNormalMatrix = addUniform("uNormalMatrix");

   GLint aPosition = addAttribute(POSITION, "aPosition");
   GLint aNormal = addAttribute(NORMAL, "aNormal");

   GLint uNumLights = addUniform("uNumLights");
   GLint uCameraPos = addUniform("uCameraPos");

   // Light
   GLint uLightPos = addUniform("uLights[0].position");
   GLint uLightColor = addUniform("uLights[0].color");
   GLint uLightConst = addUniform("uLights[0].constFalloff");
   GLint uLightLinear = addUniform("uLights[0].linearFalloff");
   GLint uLightSquare = addUniform("uLights[0].squareFalloff");
   
   // Material
   GLint uMaterialAmbient = addUniform("uMaterial.ambient");
   GLint uMaterialDiffuse = addUniform("uMaterial.diffuse");
   GLint uMaterialSpecular = addUniform("uMaterial.specular");
   GLint uMaterialEmission = addUniform("uMaterial.emission");
   GLint uMaterialShininess = addUniform("uMaterial.shininess");
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
