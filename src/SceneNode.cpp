#include "SceneNode.h"
#include "SceneGraph.h"

#include <memory>

SceneNode::SceneNode(SceneGraph *graph, const std::string &name)
   : graph(graph) {
   this->name = name;
   this->visible = true;
   this->scale = glm::vec3(1.0f);
}

SceneNode::~SceneNode() {

}

void SceneNode::draw() {

}

void SceneNode::tick() {

}