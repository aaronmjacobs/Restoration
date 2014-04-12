#include "GeometryNode.h"
#include "FancyAssert.h"
#include "Loader.h"
#include "SceneGraph.h"

#include <assimp/Importer.hpp>      // C++ importer interface

GeometryNode::GeometryNode(SceneGraph *scene, const std::string &name, ModelRef model)
   : SceneNode(scene, name), model(model) {

}

void GeometryNode::draw(MatrixStack *modelMatrixStack) {
   modelMatrixStack->push();

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

void GeometryNode::tick(const double dt) {

}