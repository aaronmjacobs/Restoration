#include "FancyAssert.h"
#include "GeometryNode.h"
#include "Loader.h"
#include "SceneGraph.h"

#include <assimp/Importer.hpp>

GeometryNode::GeometryNode(const std::string &name, ModelRef model)
   : SceneNode(name), model(model) {
}

GeometryNode::~GeometryNode() {
}

GeometryNodeRef GeometryNode::fromJson(const Json::Value &root) {
   std::string name = root["name"].asString();
   std::string modelName = root["model"].asString();

   return GeometryNodeRef(new GeometryNode(name, ModelRef()));
}

Json::Value GeometryNode::toJson() {
   Json::Value root;

   root["name"] = name;
   root["model"] = "derp";

   return root;
}

void GeometryNode::draw(MatrixStack *modelMatrixStack) {
   modelMatrixStack->push();

   // Set the shader program, and grab the matrix uniforms
   ShaderProgramRef shaderProgram = model->getMaterial()->getShaderProgram();
   shaderProgram->use();
   GLint uModelMatrix = shaderProgram->getUniform("uModelMatrix");
   GLint uNormalMatrix = shaderProgram->getUniform("uNormalMatrix");

   // Transform the model matrix
   glm::mat4 transMatrix = glm::translate(position);
   glm::mat4 rotMatrix = glm::toMat4(orientation);
   glm::mat4 scaleMatrix = glm::scale(scale);
   glm::mat4 *modelMatrix = modelMatrixStack->getMatrix();
   *modelMatrix *= transMatrix * rotMatrix * scaleMatrix;

   // Calculate the normal matrix
   glm::mat4 normal = glm::transpose(glm::inverse(*modelMatrix));

   // Update the uniforms
   glUniformMatrix4fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(*modelMatrix));
   glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normal));

   // Draw the model
   model->draw();

   // Draw each child
   for (NodeRef child : children) {
      child->draw(modelMatrixStack);
   }

   modelMatrixStack->pop();
}

void GeometryNode::tick(const float dt) {
   // Call parent class
   SceneNode::tick(dt);
}
