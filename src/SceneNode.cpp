#include "SceneNode.h"
#include "SceneGraph.h"

#include <memory>

SceneNode::SceneNode(SceneGraph *graph, const std::string &name)
   : graph(graph), name(name) {
   this->visible = true;
   this->scale = glm::vec3(1.0f);
}

SceneNode::~SceneNode() {

}

NodeRef SceneNode::findNodeByName(const std::string &name) {
   if (this->name == name) {
      return NodeRef(this);
   }

   NodeRef node(nullptr);
   for (std::list<NodeRef>::const_iterator iterator = children.begin(), end = children.end();
        iterator != end; ++iterator) {
      node = (*iterator)->findNodeByName(name);
      if (node) {
         return node;
      }
   }

   return node;
}

void SceneNode::draw() {

}

void SceneNode::tick() {

}