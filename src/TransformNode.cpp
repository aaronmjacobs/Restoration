#include "TransformNode.h"

TransformNode::TransformNode(SceneGraph *scene, const std::string &name) 
   : SceneNode(scene, name) {

}

TransformNode::~TransformNode() {
   
}

void TransformNode::tick(const double dt) {
   
}

void TransformNode::draw(MatrixStack *matrixStack) {
   matrixStack->push();

   // TODO Do transforms

   matrixStack->pop();
}