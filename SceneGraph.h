#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include "Camera.h"
#include "SceneNode.h"

#include <map>
#include <memory>

class SceneGraph {
private:
   Camera camera;
   SceneNode rootNode;
   std::map<std::string, NodeRef> nodeMap;

public:
   SceneGraph();
   ~SceneGraph();
   void draw();
   void tick();
};

#endif