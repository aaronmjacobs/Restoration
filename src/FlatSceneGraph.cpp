#include "FlatSceneGraph.h"
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
   for (SPtr<SceneObject> object : objects) {
      objectsVal.append(object->serialize());
   }
   root["objects"] = objectsVal;

   return root;
}

void FlatSceneGraph::tick(const float dt) {
   // TODO Collision handling
   for (SPtr<SceneObject> object : objects) {
      object->tick(dt);
   }
}

void FlatSceneGraph::add(SPtr<SceneObject> sceneObject) {
   SceneGraph::add(sceneObject);
   objects.push_back(sceneObject);
}

void FlatSceneGraph::remove(SPtr<SceneObject> sceneObject) {
   for (std::list<SPtr<SceneObject>>::iterator itr = objects.begin();
      itr != objects.end(); ++itr) {
      if (sceneObject == *itr) {
         objects.erase(itr);
         SceneGraph::remove(sceneObject);
         return;
      }
   }
}

void FlatSceneGraph::forEach(void (*function)(SceneObject &obj)) {
   for (SPtr<SceneObject> object : objects) {
      function(*object);
   }
}
