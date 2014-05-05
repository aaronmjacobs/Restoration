#include "FlatSceneGraph.h"
#include "PhysicalObject.h"
#include "Scene.h"
#include "SceneObject.h"

const std::string FlatSceneGraph::CLASS_NAME = "FlatSceneGraph";

FlatSceneGraph::FlatSceneGraph(SPtr<Scene> scene)
: SceneGraph(scene) {
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
   // Tick each object in the scene
   std::list<SPtr<SceneObject>>::iterator itr = objects.begin();
   while (itr != objects.end()) {
      if ((*itr)->shouldBeRemoved()) {
         // If an object should be removed, remove it
         SceneGraph::remove(*itr);
         itr = objects.erase(itr);
      } else {
         (*itr)->tick(dt);
         ++itr;
      }
   }

   // Take out any phys items that should be removed
   std::list<SPtr<PhysicalObject>>::iterator physItr = physObjects.begin();
   while (physItr != physObjects.end()) {
      if ((*physItr)->shouldBeRemoved()) {
         SceneGraph::removePhys(*physItr);
         physItr = physObjects.erase(physItr);
      } else {
         ++physItr;
      }
   }

   // Check collisions for each object in the scene
   for (SPtr<PhysicalObject> physObject : physObjects) {
      for (SPtr<PhysicalObject> other : physObjects) {
         // Don't check for collisions between the same object
         if (physObject == other) {
            continue;
         }

         // Check if the objects are colliding
         if (physObject->collidesWith(*other)) {
            // If there is a collision, handle it
            physObject->collideWith(*other);
         }
      }
   }
}

void FlatSceneGraph::add(SPtr<SceneObject> sceneObject) {
   SceneGraph::add(sceneObject);
   objects.push_back(sceneObject);
}

void FlatSceneGraph::addPhys(SPtr<PhysicalObject> physObject) {
   SceneGraph::addPhys(physObject);
   physObjects.push_back(physObject);

   // Add to the list of all scene objects
   add(physObject);
}

void FlatSceneGraph::forEach(void (*function)(SceneObject &obj)) {
   for (SPtr<SceneObject> object : objects) {
      function(*object);
   }
}

void FlatSceneGraph::forEachPhys(void (*function)(PhysicalObject &obj)) {
   for (SPtr<PhysicalObject> physObject : physObjects) {
      function(*physObject);
   }
}
