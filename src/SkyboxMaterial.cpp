#include "Camera.h"
#include "FancyAssert.h"
#include "SkyboxMaterial.h"

const std::string SkyboxMaterial::CLASS_NAME = "SkyboxMaterial";

SkyboxMaterial::SkyboxMaterial(const std::string &jsonName,
                               SPtr<ShaderProgram> shaderProgram,
                               SPtr<Camera> camera)
: Material(jsonName, shaderProgram) {
   this->camera = WPtr<Camera>(camera);
}

SkyboxMaterial::~SkyboxMaterial() {
}

Json::Value SkyboxMaterial::serialize() const {
   Json::Value root;

   // Class name
   root["@class"] = CLASS_NAME;

   // Shader program
   root["shaderProgram"] = shaderProgram->getJsonFileName();
   
   return root;
}

void SkyboxMaterial::apply(SPtr<Mesh> mesh) {
   shaderProgram->use();

   SPtr<Camera> cam = camera.lock();
   ASSERT(cam, "Skybox unable to access camera");

   GLint uModelMatrix = shaderProgram->getUniform("uModelMatrix");
   GLint uViewMatrix = shaderProgram->getUniform("uViewMatrix");
   GLint uProjMatrix = shaderProgram->getUniform("uProjMatrix");

   // Transform the model matrix
   glm::mat4 modelMatrix = glm::translate(cam->getPosition());
   glm::mat4 viewMatrix = cam->getViewMatrix();
   glm::mat4 projMatrix = cam->getProjectionMatrix();

   // Update the uniforms
   glUniformMatrix4fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
   glUniformMatrix4fv(uViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
   glUniformMatrix4fv(uProjMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix));
}
