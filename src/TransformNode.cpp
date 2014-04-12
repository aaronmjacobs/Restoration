#include "TransformNode.h"

TransformNode::TransformNode(SceneGraph *scene, const std::string &name) 
   : SceneNode(scene, name) {

}

TransformNode::~TransformNode() {
   
}

void TransformNode::tick(const double dt) {
   SceneNode::tick(dt);
}

void TransformNode::draw(MatrixStack *modelMatrixStack) {
   modelMatrixStack->push();

   // Transform the model matrix
   glm::mat4 transMatrix = glm::translate(position);
   glm::mat4 rotMatrix = glm::toMat4(orientation);
   glm::mat4 scaleMatrix = glm::scale(scale);
   glm::mat4 *modelMatrix = modelMatrixStack->getMatrix();
   *modelMatrix *= transMatrix * rotMatrix * scaleMatrix;

   // Draw each child
   for (NodeRef child : children) {
      child->draw(modelMatrixStack);
   }

   modelMatrixStack->pop();
}