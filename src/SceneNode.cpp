#include "SceneNode.h"
#include "SceneGraph.h"

#include <memory>

SceneNode::SceneNode(SceneGraph *scene, const std::string &name)
   : scene(scene), name(name) {
   this->scale = glm::vec3(1.0f);
}

SceneNode::~SceneNode() {

}

NodeRef SceneNode::findNodeByName(const std::string &name) {
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

void SceneNode::translateBy(glm::vec3 trans) {
   position += trans;
}

void SceneNode::rotateBy(glm::quat rot) {
   orientation *= rot;
}

void SceneNode::scaleBy(glm::vec3 scale) {
   this->scale *= scale;
}

void SceneNode::tick(const double dt) {
   // Tick each child
   for (NodeRef child : children) {
      child->tick(dt);
   }
}