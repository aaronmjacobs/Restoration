#ifndef GRID_SCENE_GRAPH_H
#define GRID_SCENE_GRAPH_H

#include "Camera.h"
#include "GLIncludes.h"
#include "SceneGraph.h"
#include "TickListener.h"
#include "UniformGrid.h"

#include <vector>

class GridSceneGraph : public SceneGraph {
private:
   std::vector<SPtr<SceneObject>> objects;
   UniformGrid<SPtr<PhysicalObject>> staticPhysObjects;
   UniformGrid<SPtr<PhysicalObject>> movablePhysObjects;
   bool staticObjectsNeedUpdate;

   std::vector<SPtr<SceneObject>> objectsToAdd;
   std::vector<SPtr<PhysicalObject>> physObjectsToAdd;

public:
   static const std::string CLASS_NAME;

   GridSceneGraph(SPtr<Scene> scene);
   virtual ~GridSceneGraph();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   /**
    * Steps |dt| seconds through time.
    */
   virtual void tick(const float dt);

   virtual void staticObjectsModified();
   virtual void add(SPtr<SceneObject> sceneObject);
   virtual void addPhys(SPtr<PhysicalObject> physObject);
   virtual void forEach(void (*function)(SceneObject &obj));
   virtual void forEachPhys(void (*function)(PhysicalObject &obj));

   virtual void updateAddedItems();

   /**
    * Goes through each phys object and finds the first thing the mouse collides with
    */
   virtual SPtr<PhysicalObject> mouseCollides(double xPos, double yPos);
};

#endif
