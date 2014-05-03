#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include "Serializable.h"
#include "TickListener.h"
#include "Types.h"

#include <map>
#include <list>
#include <string>

class SceneObject;

class SceneGraph : public Serializable, public TickListener {
private:
   std::map<std::string, WPtr<SceneObject>> objectMap;

public:
   static const std::string CLASS_NAME;

   SceneGraph();
   virtual ~SceneGraph();

   /**
    * Gets the name of the folder the serializable will be written to.
    */
   virtual std::string getJsonFolderName() const {
      return "scenes";
   }

   virtual void add(SPtr<SceneObject> sceneObject);
   virtual void remove(SPtr<SceneObject> sceneObject);
   WPtr<SceneObject> find(const std::string &name);
   virtual void forEach(void (*function)(SceneObject &obj)) = 0;
};

#endif
