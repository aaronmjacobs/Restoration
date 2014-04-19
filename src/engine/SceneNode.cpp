#include "SceneGraph.h"
#include "SceneNode.h"

#include <memory>

SceneNode::SceneNode(Scene *scene, const std::string &name)
   : scene(scene), name(name) {
   this->scale = glm::vec3(1.0f);
}

SceneNode::~SceneNode() {
}

void SceneNode::addChild(NodeRef node) {
   children.push_back(node);
}

void SceneNode::removeChild(NodeRef node) {
   children.remove(node);
}

NodeRef SceneNode::findNodeByName(const std::string &name) {
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

void SceneNode::translateBy(glm::vec3 trans) {
   position += trans;
}

void SceneNode::rotateBy(glm::quat rot) {
   orientation *= rot;
}

void SceneNode::scaleBy(glm::vec3 scale) {
   this->scale *= scale;
}

void SceneNode::tick(const float dt) {
   // Tick each child
   for (NodeRef child : children) {
      child->tick(dt);
   }
}
