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

   model->draw();

   for (NodeRef child : children) {
      child->draw(modelMatrixStack);
   }

   modelMatrixStack->pop();
}

void GeometryNode::tick(const double dt) {

}