#include "FancyAssert.h"
#include "SceneGraph.h"

SceneGraph::SceneGraph() {
}

SceneGraph::~SceneGraph() {
}

void SceneGraph::addChild(NodeRef node) {
   children.push_back(node);
}

void SceneGraph::removeChild(NodeRef node) {
   children.remove(node);
}

void SceneGraph::tick(const float dt) {
   // Tick each child
   for (NodeRef child : children) {
      child->tick(dt);
   }
}

NodeRef SceneGraph::findNodeByName(const std::string &name) {
   NodeRef node(nullptr);

   for (NodeRef child : children) {
      // If a direct child matches, return it.
      if (child->getName() == name) {
         return child;
      }

      // If the child does not match, recursively check its children.
      node = child->findNodeByName(name);
      if (node) {
         return node;
      }
   }

   return node;
}
