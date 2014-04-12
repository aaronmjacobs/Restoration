#include "TransformNode.h"

TransformNode::TransformNode(SceneGraph *scene, const std::string &name) 
   : SceneNode(scene, name) {

}

TransformNode::~TransformNode() {
   
}

void TransformNode::tick(const double dt) {
   
}

void TransformNode::draw(MatrixStack *modelMatrixStack) {
   modelMatrixStack->push();

   // TODO Do transforms

   modelMatrixStack->pop();
}