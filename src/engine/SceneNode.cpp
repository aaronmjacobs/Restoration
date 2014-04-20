#include "SceneGraph.h"
#include "SceneNode.h"

#include <memory>

const std::string SceneNode::CLASS_NAME = "SceneNode";
const std::string SceneNode::JSON_FOLDER_PATH = "data/scenenode/";

SceneNode::SceneNode(const std::string &jsonFileName, const std::string &name)
   : Serializable(jsonFileName), name(name) {
   this->scale = glm::vec3(1.0f);
}

SceneNode::~SceneNode() {
}

Json::Value SceneNode::serialize() const {
   Json::Value root;

   // Class name
   root["@class"] = CLASS_NAME;

   // Name of the node
   root["name"] = name;

   // Position of the node
   Json::Value posValue;
   posValue["x"] = position.x;
   posValue["y"] = position.y;
   posValue["z"] = position.z;
   root["position"] = posValue;

   // Orientation of the node
   Json::Value oriValue;
   oriValue["w"] = orientation.w;
   oriValue["x"] = orientation.x;
   oriValue["y"] = orientation.y;
   oriValue["z"] = orientation.z;
   root["orientation"] = oriValue;

   // Scale of the node
   Json::Value scaleValue;
   scaleValue["x"] = scale.x;
   scaleValue["y"] = scale.y;
   scaleValue["z"] = scale.z;
   root["scale"] = scaleValue;

   Json::Value childrenValue;
   for (NodeRef child : children) {
      Json::Value childValue = child->serialize();
      childrenValue.append(childValue);
   }
   root["children"] = childrenValue;

   return root;
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
