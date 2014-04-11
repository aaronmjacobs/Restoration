#include "GeometryNode.h"
#include "FancyAssert.h"
#include "Loader.h"
#include "SceneGraph.h"

#include <assimp/Importer.hpp>      // C++ importer interface

GeometryNode::GeometryNode(SceneGraph *scene, const std::string &name, ModelRef model)
   : SceneNode(scene, name), model(model) {

}

void GeometryNode::draw(MatrixStack *matrixStack) {
   matrixStack->push();

   model->draw();

   for (NodeRef child : children) {
      child->draw(matrixStack);
   }

   matrixStack->pop();
}

void GeometryNode::tick(const double dt) {

}