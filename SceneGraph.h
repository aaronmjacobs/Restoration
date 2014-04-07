#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include "Camera.h"
#include "MatrixStack.h"
#include "SceneNode.h"

#include <map>
#include <memory>

class SceneGraph {
private:
   Camera camera;
   NodeRef rootNode;
   MatrixStack matrixStack;
   std::map<std::string, NodeRef> nodeMap;

public:
   SceneGraph();
   ~SceneGraph();
   void setRoot(NodeRef node) {
      rootNode = node;
   }
   void draw();
   void tick();
   MatrixStack* getMatrixStack() {
      return &matrixStack;
   }
   NodeRef findNodeByName(const std::string &name);
};

#endif