#include "GridSceneGraph.h"
#include "PhysicalObject.h"
#include "Scene.h"
#include "SceneObject.h"
#include "Camera.h"

const std::string GridSceneGraph::CLASS_NAME = "GridSceneGraph";

GridSceneGraph::GridSceneGraph(SPtr<Scene> scene)
: SceneGraph(scene), staticPhysObjects(50, 2, glm::vec2(-100.0f, 800.0f), glm::vec2(100.0f, 100.0f)), movablePhysObjects(50, 2, glm::vec2(-100.0f, 800.0f), glm::vec2(100.0f, 100.0f)), staticObjectsNeedUpdate(false) {
}

GridSceneGraph::~GridSceneGraph() {
}

void GridSceneGraph::staticObjectsModified() {
   staticObjectsNeedUpdate = true;
}

Json::Value GridSceneGraph::serialize() const {
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

void GridSceneGraph::tick(const float dt) {
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

   // Remove any objects that should be removed, and update the positions
   // of objects in the scene
   if (staticObjectsNeedUpdate) {
      staticObjectsNeedUpdate = false;
      staticPhysObjects.update();
   }
   movablePhysObjects.update();

   // Check collisions for each object in the scene
   std::vector<GridNode<SPtr<PhysicalObject>>>& staticNodes = staticPhysObjects.getNodes();
   std::vector<GridNode<SPtr<PhysicalObject>>>& movableNodes = movablePhysObjects.getNodes();
   std::vector<GridElement<SPtr<PhysicalObject>>>& movableElements = movablePhysObjects.getElements();

   for (GridElement<SPtr<PhysicalObject>> physElement : movableElements) {
      for (size_t nodeIndex : physElement.nodes) {
         for (SPtr<PhysicalObject> other : staticNodes[nodeIndex].elements) {
            // Check if the objects are colliding
            if (physElement.element->collidesWith(*other)) {
               // If there is a collision, handle it
               physElement.element->collideWith(*other);
            }
         }

         for (SPtr<PhysicalObject> other : movableNodes[nodeIndex].elements) {
            // Don't check for collisions between the same object
            if (physElement.element == other) {
               continue;
            }

            // Check if the objects are colliding
            if (physElement.element->collidesWith(*other)) {
               // If there is a collision, handle it
               physElement.element->collideWith(*other);
            }
         }
      }
   }
}

void GridSceneGraph::add(SPtr<SceneObject> sceneObject) {
   SceneGraph::add(sceneObject);
   objects.push_back(sceneObject);
}

void GridSceneGraph::addPhys(SPtr<PhysicalObject> physObject) {
   SceneGraph::addPhys(physObject);
   if (physObject->canMove()) {
      movablePhysObjects.insert(physObject);
   } else {
      staticPhysObjects.insert(physObject);
   }

   // Add to the list of all scene objects
   add(physObject);
}

void GridSceneGraph::forEach(void(*function)(SceneObject &obj)) {
   for (SPtr<SceneObject> object : objects) {
      function(*object);
   }
}

void GridSceneGraph::forEachPhys(void (*function)(PhysicalObject &obj)) {
   for (GridElement<SPtr<PhysicalObject>> physObjectElement : staticPhysObjects.getElements()) {
      function(*physObjectElement.element);
   }

   for (GridElement<SPtr<PhysicalObject>> physObjectElement : movablePhysObjects.getElements()) {
      function(*physObjectElement.element);
   }
}

SPtr<PhysicalObject> GridSceneGraph::mouseCollides(double xPos, double yPos) {
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

   std::vector<GridElement<SPtr<PhysicalObject>>>& staticElements = staticPhysObjects.getElements();
   std::vector<GridElement<SPtr<PhysicalObject>>>& movableElements = movablePhysObjects.getElements();

   for (GridElement<SPtr<PhysicalObject>> physElement : staticElements) {
      objPos = physElement.element->getPosition();
		objRay = objPos - near;
		glm::vec3 rayIntersect = glm::normalize(mouseRay) * glm::length(objRay) + c->getPosition();

		if ((physElement.element->getBounds()).contains(rayIntersect)) {
			if (!minDistSet|| (newDist = glm::length(objRay)) < minDist) {
            minDistSet = true;
				minDist = newDist;
				obj = physElement.element;
			}
		}
   }

   for (GridElement<SPtr<PhysicalObject>> physElement : movableElements) {
      objPos = physElement.element->getPosition();
		objRay = objPos - near;
		glm::vec3 rayIntersect = glm::normalize(mouseRay) * glm::length(objRay) + c->getPosition();

		if ((physElement.element->getBounds()).contains(rayIntersect)) {
			if (!minDistSet|| glm::length(objRay) < minDist) {
				newDist = glm::length(objRay);
				minDistSet = true;
				minDist = newDist;
				obj = physElement.element;
			}
		}
   }

	return obj;
}
