#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include "Types.h"

class SceneObject;

class SceneNode {
protected:
   SPtr<SceneObject> const object;

public:
   SceneNode(SPtr<SceneObject> object);
   virtual ~SceneNode();
   SPtr<SceneObject> getObject() {
      return object;
   }
};

#endif
