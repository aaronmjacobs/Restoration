#include "SceneGraph.h"
#include "FancyAssert.h"

SceneGraph::SceneGraph()
   : rootNode(nullptr) {
}

SceneGraph::~SceneGraph() {

}

void SceneGraph::draw() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Camera position
   //glUniform3fv(uCameraPos, 1, glm::value_ptr(camera.getPosition()));

   //glUniformMatrix4fv(uViewMatrix, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));

   if (rootNode != nullptr) {
      rootNode->draw();
   }
}

void SceneGraph::tick() {
   if (rootNode != nullptr) {
      rootNode->tick();
   }
}

NodeRef SceneGraph::findNodeByName(const std::string &name) {
   if (rootNode == nullptr) {
      return NodeRef(nullptr);
   }

   NodeRef node(nullptr);
   std::list<NodeRef> rootList = rootNode->getChildren();
   for (std::list<NodeRef>::const_iterator iterator = rootList.begin(), end = rootList.end();
        iterator != end; ++iterator) {
      node = (*iterator)->findNodeByName(name);
      if (node) {
         return node;
      }
   }

   return node;
}