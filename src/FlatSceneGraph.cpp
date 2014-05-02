#include "FlatSceneGraph.h"
#include "SceneNode.h"
#include "SceneObject.h"

const std::string FlatSceneGraph::CLASS_NAME = "FlatSceneGraph";

FlatSceneGraph::FlatSceneGraph() {
}

FlatSceneGraph::~FlatSceneGraph() {
}

Json::Value FlatSceneGraph::serialize() const {
   Json::Value root;

   root["@class"] = CLASS_NAME;

   Json::Value objectsVal;
   for (SceneNode node : nodes) {
      objectsVal.append(node.getObject()->serialize());
   }
   root["objects"] = objectsVal;

   return root;
}

void FlatSceneGraph::tick(const float dt) {
   // TODO Collision handling
   for (SceneNode node : nodes) {
      node.getObject()->tick(dt);
   }
}

void FlatSceneGraph::add(SPtr<SceneObject> sceneObject) {
   SceneGraph::add(sceneObject);
   nodes.push_back(SceneNode(sceneObject));
}

void FlatSceneGraph::remove(SPtr<SceneObject> sceneObject) {
   for (std::list<SceneNode>::iterator itr = nodes.begin();
      itr != nodes.end(); ++itr) {
      if (sceneObject == itr->getObject()) {
         nodes.erase(itr);
         SceneGraph::remove(sceneObject);
         return;
      }
   }
}

void FlatSceneGraph::forEach(void (*function)(SceneObject &obj)) {
   for (SceneNode node : nodes) {
      function(*node.getObject());
   }
}
