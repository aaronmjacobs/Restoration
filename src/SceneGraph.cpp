#include "FancyAssert.h"
#include "SceneGraph.h"
#include "SceneObject.h"

const std::string SceneGraph::CLASS_NAME = "SceneGraph";

SceneGraph::SceneGraph() {
}

SceneGraph::~SceneGraph() {
}

void SceneGraph::add(SPtr<SceneObject> sceneObject) {
   const std::string &objectName = sceneObject->getName();

   // If the object has a name, make sure it doesn't match anything
   // already in the graph
   if (objectName.length() > 0) {
      std::map<std::string, WPtr<SceneObject>>::iterator it = objectMap.find(objectName);
      ASSERT(it == objectMap.end(), "Scene already has object with name: %s", objectName.c_str());
   }

   objectMap[objectName] = WPtr<SceneObject>(sceneObject);
}

void SceneGraph::remove(SPtr<SceneObject> sceneObject) {
   const std::string &objectName = sceneObject->getName();

   // If the object has a name, remove it from the map
   if (objectName.length() > 0) {
      std::map<std::string, WPtr<SceneObject>>::iterator it = objectMap.find(objectName);
      ASSERT(it != objectMap.end(), "Scene has no object with name: %s", objectName.c_str());

      objectMap.erase(objectName);
   }
}

WPtr<SceneObject> SceneGraph::find(const std::string &name) {
   ASSERT(name.length() > 0, "Can't look up object with empty name: %s", name.c_str());

   std::map<std::string, WPtr<SceneObject>>::iterator it = objectMap.find(name);
   ASSERT(it != objectMap.end(), "Scene has no object with name: %s", name.c_str());

   return objectMap[name];
}
