#include "FancyAssert.h"
#include "PhysicalObject.h"
#include "Scene.h"
#include "SceneGraph.h"
#include "SceneObject.h"

const std::string SceneGraph::CLASS_NAME = "SceneGraph";

SceneGraph::SceneGraph(SPtr<Scene> scene)
: scene(WPtr<Scene>(scene)) {
}

SceneGraph::~SceneGraph() {
}

void SceneGraph::staticObjectsModified() {
}

void SceneGraph::add(SPtr<SceneObject> sceneObject) {
   const std::string &objectName = sceneObject->getName();

   // If the object has a name, make sure it doesn't match anything
   // already in the graph
   if (objectName.length() > 0) {
      ObjectMap::iterator it = objectMap.find(objectName);
      ASSERT(it == objectMap.end(), "Scene already has object with name: %s", objectName.c_str());
   }

   objectMap[objectName] = WPtr<SceneObject>(sceneObject);
}

void SceneGraph::addPhys(SPtr<PhysicalObject> physObject) {
   const std::string &objectName = physObject->getName();

   // If the object has a name, make sure it doesn't match anything
   // already in the graph
   if (objectName.length() > 0) {
      //PhysObjectMap::iterator it = physObjectMap.find(objectName);
      //ASSERT(it == physObjectMap.end(), "Scene already has phys object with name: %s", objectName.c_str());
   }

   physObjectMap[objectName] = WPtr<PhysicalObject>(physObject);
}

void SceneGraph::remove(SPtr<SceneObject> sceneObject) {
   const std::string &objectName = sceneObject->getName();

   // If the object has a name, remove it from the map
   if (objectName.length() > 0) {
      ObjectMap::iterator it = objectMap.find(objectName);
      ASSERT(it != objectMap.end(), "Scene has no object with name: %s", objectName.c_str());

      objectMap.erase(objectName);
   }
}

void SceneGraph::removePhys(SPtr<PhysicalObject> physObject) {
   const std::string &objectName = physObject->getName();

   // If the object has a name, remove it from the map
   if (objectName.length() > 0) {
      PhysObjectMap::iterator it = physObjectMap.find(objectName);
      ASSERT(it != physObjectMap.end(), "Scene has no phys object with name: %s", objectName.c_str());

      physObjectMap.erase(objectName);
   }
}

WPtr<SceneObject> SceneGraph::find(const std::string &name) {
   ASSERT(name.length() > 0, "Can't look up object with empty name: %s", name.c_str());

   ObjectMap::iterator it = objectMap.find(name);
   ASSERT(it != objectMap.end(), "Scene has no object with name: %s", name.c_str());

   return it->second;
}

WPtr<PhysicalObject> SceneGraph::findPhys(const std::string &name) {
   ASSERT(name.length() > 0, "Can't look up phys object with empty name: %s", name.c_str());

   PhysObjectMap::iterator it = physObjectMap.find(name);
   ASSERT(it != physObjectMap.end(), "Scene has no phys object with name: %s", name.c_str());

   return it->second;
}
