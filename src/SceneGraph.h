#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include "Camera.h"
#include "SceneNode.h"

#include <memory>

class SceneGraph {
private:
   Camera camera;
   std::list<NodeRef> children;

public:
   SceneGraph();
   ~SceneGraph();
   void addChild(NodeRef node) {
      children.push_back(node);
   }
   const std::list<NodeRef>& getChildren() {
      return children;
   }
   Camera* getCamera() {
      return &camera;
   }
   void tick(const double dt);
   NodeRef findNodeByName(const std::string &name);
};

#endif