#ifndef FLAT_SCENE_GRAPH_H
#define FLAT_SCENE_GRAPH_H

#include "SceneGraph.h"

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
};

#endif
