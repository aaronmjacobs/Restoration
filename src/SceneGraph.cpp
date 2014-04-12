#include "SceneGraph.h"
#include "FancyAssert.h"

SceneGraph::SceneGraph() {
}

SceneGraph::~SceneGraph() {
}

void SceneGraph::tick(const double dt) {
   for (NodeRef child : children) {
      child->tick(dt);
   }
}

NodeRef SceneGraph::findNodeByName(const std::string &name) {
   NodeRef node(nullptr);

   for (NodeRef child : children) {
      if (child->getName() == name) {
         return child;
      }

      node = child->findNodeByName(name);
      if (node) {
         return node;
      }
   }

   return node;
}