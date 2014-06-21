#include "FlatSceneGraph.h"
#include "PhysicalObject.h"
#include "Scene.h"
#include "SceneObject.h"
#include "Camera.h"

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
      if (object->shouldBeSerialized()) {
         objectsVal.append(object->serialize());
      }
   }
   root["objects"] = objectsVal;

   return root;
}

void FlatSceneGraph::tick(const float dt) {
   updateAddedItems();

   // Tick each object in the scene
   std::vector<SPtr<SceneObject>>::iterator itr = objects.begin();

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
   std::vector<SPtr<PhysicalObject>>::iterator physItr = physObjects.begin();
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
      if (!physObject->canMove()) {
         continue;
      }

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
   ASSERT(sceneObject, "Can't add null object");
   objectsToAdd.push_back(sceneObject);
}

void FlatSceneGraph::addPhys(SPtr<PhysicalObject> physObject) {
   ASSERT(physObject, "Can't add null phys object");
   physObjectsToAdd.push_back(physObject);

   // Add to the list of all scene objects
   add(physObject);
}

void FlatSceneGraph::forEach(void(*function)(SceneObject &obj)) {
   for (SPtr<SceneObject> object : objects) {
      function(*object);
   }
}

void FlatSceneGraph::forEachPhys(void (*function)(PhysicalObject &obj)) {
   for (SPtr<PhysicalObject> physObject : physObjects) {
      function(*physObject);
   }
}

void FlatSceneGraph::updateAddedItems() {
   // Add any pending objects to the scene
   std::vector<SPtr<SceneObject>>::iterator pendingItr = objectsToAdd.begin();
   while (pendingItr != objectsToAdd.end()) {
      SceneGraph::add(*pendingItr);
      objects.push_back(*pendingItr);

      pendingItr = objectsToAdd.erase(pendingItr);
   }

   std::vector<SPtr<PhysicalObject>>::iterator pendingPhysItr = physObjectsToAdd.begin();
   while (pendingPhysItr != physObjectsToAdd.end()) {
      SceneGraph::addPhys(*pendingPhysItr);
      physObjects.push_back(*pendingPhysItr);

      pendingPhysItr = physObjectsToAdd.erase(pendingPhysItr);
   }
}

SPtr<PhysicalObject> FlatSceneGraph::mouseCollides(double xPos, double yPos) {
	SPtr<PhysicalObject> obj;
	glm::mat4 view, proj;
	glm::vec3 objPos, near, far, objRay, mouseRay, mousePos;
	glm::vec4 viewP;

	double minDist = 0.0, newDist = 0.0;
    bool minDistSet = false;

	SPtr<Scene> s = scene.lock();
	if (!s) {
		return SPtr<PhysicalObject>();
	}
	SPtr<Camera> c = s->getCamera().lock();
	if (!c) {
		return SPtr<PhysicalObject>();
	}

	proj = c->getProjectionMatrix();
	view = c->getViewMatrix();
	viewP = glm::vec4(0, 0, c->getWindowWidth(), c->getWindowHeight());
	mousePos = glm::vec3(xPos, c->getWindowHeight() - yPos, 0.0);

	near = glm::unProject(mousePos, view, proj, viewP);
	mousePos.z = 1.0;
	far = glm::unProject(mousePos, view, proj, viewP);
	mouseRay = far - near;
	for (SPtr<PhysicalObject> physObject : physObjects) {
		objPos = physObject->getPosition();
		objRay = objPos - near;
		glm::vec3 rayIntersect = glm::normalize(mouseRay) * glm::length(objRay) + c->getPosition();

		if ((physObject->getBounds()).contains(rayIntersect)) {
			if (!minDistSet|| glm::length(objRay) < minDist) {
				newDist = glm::length(objRay);
				minDistSet = true;
				minDist = newDist;
				obj = physObject;
			}
		}
	}
	return obj;
}
