#ifndef FLAT_SCENE_GRAPH_H
#define FLAT_SCENE_GRAPH_H

#include "SceneGraph.h"
#include "GLIncludes.h"
#include "Camera.h"
#include "TickListener.h"

#include <list>

class FlatSceneGraph : public SceneGraph {
private:
   std::list<SPtr<SceneObject>> objects;
   std::list<SPtr<PhysicalObject>> physObjects;

public:
   static const std::string CLASS_NAME;

   FlatSceneGraph(SPtr<Scene> scene);
   virtual ~FlatSceneGraph();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   /**
    * Steps |dt| seconds through time.
    */
   virtual void tick(const float dt);

   virtual void add(SPtr<SceneObject> sceneObject);
   virtual void addPhys(SPtr<PhysicalObject> physObject);
   virtual void forEach(void (*function)(SceneObject &obj));
   virtual void forEachPhys(void (*function)(PhysicalObject &obj));

   /**
    * Goes through each phys object and finds the first thing the mouse collides with
	*/
   virtual SPtr<PhysicalObject> mouseCollides(double xPos, double yPos);

   virtual void printVec(glm::vec3 ray);
};

#endif
