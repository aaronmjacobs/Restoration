#include "FancyAssert.h"
#include "Geometry.h"
#include "Material.h"
#include "MatrixStack.h"
#include "Model.h"

const std::string Geometry::CLASS_NAME = "Geometry";

Geometry::Geometry(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
   : SceneObject(scene, name) {
   ASSERT(model, "Model is null");
   this->model = model;
}

Geometry::~Geometry() {
}

Json::Value Geometry::serialize() const {
   Json::Value root = SceneObject::serialize();

   // Class name
   root["@class"] = CLASS_NAME;

   // Model
   root["model"] = model->serialize();

   return root;
}

SPtr<Model> Geometry::getModel() {
   return model;
}

void Geometry::draw() {
   // Set the shader program, and grab the matrix uniforms
   SPtr<ShaderProgram> shaderProgram = model->getMaterial()->getShaderProgram();
   shaderProgram->use();

   GLint uModelMatrix = shaderProgram->getUniform("uModelMatrix");
   GLint uNormalMatrix = shaderProgram->getUniform("uNormalMatrix");

   // Transform the model matrix
   glm::mat4 transMatrix = glm::translate(position);
   glm::mat4 rotMatrix = glm::toMat4(orientation);
   glm::mat4 scaleMatrix = glm::scale(scale);
   glm::mat4 modelMatrix = transMatrix * rotMatrix * scaleMatrix;

   // Calculate the normal matrix
   glm::mat4 normal = glm::transpose(glm::inverse(modelMatrix));

   // Update the uniforms
   glUniformMatrix4fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
   glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normal));

   // Draw the model
   model->draw();
}

void Geometry::tick(const float dt) {
}
