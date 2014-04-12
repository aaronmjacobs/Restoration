#include "GeometryNode.h"
#include "FancyAssert.h"
#include "Loader.h"
#include "SceneGraph.h"

#include <assimp/Importer.hpp>      // C++ importer interface

#include <iostream>

GeometryNode::GeometryNode(SceneGraph *scene, const std::string &name, ModelRef model)
   : SceneNode(scene, name), model(model) {

}

void GeometryNode::draw(MatrixStack *modelMatrixStack) {
   modelMatrixStack->push();

   ShaderProgramRef shaderProgram = model->getMaterial()->getShaderProgram();
   shaderProgram->use();
   GLint uModelMatrix = shaderProgram->getUniform("uModelMatrix");
   GLint uNormalMatrix = shaderProgram->getUniform("uNormalMatrix");

   // TODO Do other transforms
   glm::mat4 *modelMatrix = modelMatrixStack->getMatrix();
   *modelMatrix = glm::translate(*modelMatrix, position);

   glm::mat4 normal = glm::transpose(glm::inverse(*modelMatrix));
   glUniformMatrix4fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(*modelMatrix));
   glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normal));

   model->draw();

   for (NodeRef child : children) {
      child->draw(modelMatrixStack);
   }

   modelMatrixStack->pop();
}

void GeometryNode::tick(const double dt) {

}