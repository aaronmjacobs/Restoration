#include "Shader.h"

#include "FancyAssert.h"
#include "Utils.h"

Shader::Shader(const GLenum type, const std::string &fileName) {
   this->id = glCreateShader(type);
   this->type = type;
   this->fileName = fileName;
}

Shader::~Shader() {
   glDeleteShader(id);
}

void Shader::compile() {
   std::string source = Utils::readFromFile(fileName.c_str());
   const char *sourceData = source.c_str();

   glShaderSource(id, 1, &sourceData, NULL);
   glCompileShader(id);

   // Check if the shader compiled successfully
   GLint status;
   glGetShaderiv(id, GL_COMPILE_STATUS, &status);
   if (status == GL_TRUE) {
      return;
   }

   // If compilation failed, find out why, and report it

   GLint infoLogLength;
   glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);

   GLchar *strInfoLog = new GLchar[infoLogLength + 1];
   glGetShaderInfoLog(id, infoLogLength, NULL, strInfoLog);

   const char *strShaderType = NULL;
   switch (type) {
   case GL_VERTEX_SHADER:
      strShaderType = "vertex";
      break;
   case GL_GEOMETRY_SHADER:
      strShaderType = "geometry";
      break;
   case GL_FRAGMENT_SHADER:
      strShaderType = "fragment";
      break;
   }

   ASSERT(false, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
}

GLint Shader::getID() const {
   return id;
}