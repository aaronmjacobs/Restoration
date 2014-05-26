#include "SimpleMaterial.h"

const std::string SimpleMaterial::CLASS_NAME = "SimpleMaterial";

SimpleMaterial::SimpleMaterial(const std::string &jsonFileName, SPtr<ShaderProgram> shaderProgram)
: Material(jsonFileName, shaderProgram) {
}

SimpleMaterial::~SimpleMaterial() {
}

Json::Value SimpleMaterial::serialize() const {
   Json::Value root;

   // Class name
   root["@class"] = CLASS_NAME;

   // Shader program
   root["shaderProgram"] = shaderProgram->getJsonFileName();

   return root;
}

void SimpleMaterial::apply(const RenderData &renderData, const Mesh &mesh) {
   shaderProgram->use();
}

void SimpleMaterial::disable() {
   shaderProgram->disable();
}
