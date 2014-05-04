#ifndef FLAT_SCENE_GRAPH_H
#define FLAT_SCENE_GRAPH_H

#include "SceneGraph.h"

#include <list>

class PhysicalObject;

class FlatSceneGraph : public SceneGraph {
private:
   std::list<SPtr<SceneObject>> objects;

public:
   static const std::string CLASS_NAME;

   FlatSceneGraph();
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
   virtual void remove(SPtr<SceneObject> sceneObject);
   virtual void forEach(void (*function)(SceneObject &obj));
};

#endif
