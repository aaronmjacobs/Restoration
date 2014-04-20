#include "FancyAssert.h"
#include "Shader.h"
#include "IOUtils.h"

const std::string Shader::CLASS_NAME = "Shader";
const std::string Shader::JSON_FOLDER_PATH = "data/shader/";

Shader::Shader(const std::string &jsonFileName, const GLenum type, const std::string &fileName)
   : Serializable(jsonFileName), type(type), fileName(fileName) {
   this->id = glCreateShader(type);
}

Shader::~Shader() {
   glDeleteShader(id);
}

Json::Value Shader::serialize() const {
   Json::Value root;

   // Class name
   root["@class"] = CLASS_NAME;

   std::string typeName;
   if (type == GL_VERTEX_SHADER) {
      typeName = "vertex";
   } else if (type == GL_FRAGMENT_SHADER) {
      typeName = "fragment";
   } else if (type == GL_GEOMETRY_SHADER) {
      typeName = "geometry";
   }
   root["type"] = typeName;

   root["fileName"] = fileName;

   return root;
}

void Shader::compile() {
   // Load the shader source from the file
   std::string source = IOUtils::readFromFile(fileName);
   const char *sourceData = source.c_str();

   // Set and compile the source
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
