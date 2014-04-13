#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include "Camera.h"
#include "SceneNode.h"

#include <memory>

class SceneGraph {
private:
   Camera camera;
   std::list<NodeRef> children;

   bool forward, backward, left, right;
   bool leftMouse;
   double mouseX, mouseY;

public:
   SceneGraph();
   ~SceneGraph();
   void onKeyEvent(int key, int action);
   void onMouseEvent(int button, int action);
   void onMouseMotionEvent(double xPos, double yPos);
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