#include "TransformNode.h"

const std::string TransformNode::CLASS_NAME = "TransformNode";

TransformNode::TransformNode(Scene *scene, const std::string &jsonFileName, const std::string &name) 
   : SceneNode(scene, jsonFileName, name) {
}

TransformNode::~TransformNode() {
}

Json::Value TransformNode::serialize() const {
   Json::Value root = SceneNode::serialize();

   // Class name
   root["@class"] = CLASS_NAME;

   return root;
}

void TransformNode::tick(const float dt) {
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
