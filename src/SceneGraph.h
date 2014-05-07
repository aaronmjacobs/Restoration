#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include "Serializable.h"
#include "TickListener.h"
#include "Types.h"

#include <map>
#include <string>

class PhysicalObject;
class Scene;
class SceneObject;

typedef std::map<std::string, WPtr<SceneObject>> ObjectMap;
typedef std::map<std::string, WPtr<PhysicalObject>> PhysObjectMap;

class SceneGraph : public Serializable, public TickListener {
private:
   ObjectMap objectMap;
   PhysObjectMap physObjectMap;

protected:
   WPtr<Scene> scene;
   void remove(SPtr<SceneObject> sceneObject);
   void removePhys(SPtr<PhysicalObject> physObject);

public:
   static const std::string CLASS_NAME;

   SceneGraph(SPtr<Scene> scene);
   virtual ~SceneGraph();

   virtual void add(SPtr<SceneObject> sceneObject);
   virtual void addPhys(SPtr<PhysicalObject> physObject);
   WPtr<SceneObject> find(const std::string &name);
   WPtr<PhysicalObject> findPhys(const std::string &name);
   virtual void forEach(void (*function)(SceneObject &obj, unsigned int renderState), unsigned int renderState) = 0;
   virtual void forEachPhys(void (*function)(PhysicalObject &obj)) = 0;
};

#endif
