#include "FancyAssert.h"
#include "SceneGraph.h"

SceneGraph::SceneGraph() {
}

SceneGraph::~SceneGraph() {
}

void SceneGraph::onKeyEvent(int key, int action) {
   // Set camera motion state
   if (action == GLFW_PRESS) {
      if (key == GLFW_KEY_W) {
         forward = true;
      } else if (key == GLFW_KEY_S) {
         backward = true;
      } else if (key == GLFW_KEY_A) {
         left = true;
      } else if (key == GLFW_KEY_D) {
         right = true;
      }
   } else if (action == GLFW_RELEASE) {
      if (key == GLFW_KEY_W) {
         forward = false;
      } else if (key == GLFW_KEY_S) {
         backward = false;
      } else if (key == GLFW_KEY_A) {
         left = false;
      } else if (key == GLFW_KEY_D) {
         right = false;
      }
   }
}

void SceneGraph::onMouseEvent(int button, int action) {
   if (button == GLFW_MOUSE_BUTTON_LEFT) {
      leftMouse = action == GLFW_PRESS;
   }
}

void SceneGraph::onMouseMotionEvent(double xPos, double yPos) {
   // Update camera orientation
   const static float MOUSE_SCALE = 0.005f;
   if (leftMouse) {
      float dPhi = -(yPos - mouseY) * MOUSE_SCALE;
      float dTheta = (xPos - mouseX) * MOUSE_SCALE;
      camera.rotate(dPhi, dTheta);
   }

   mouseX = xPos;
   mouseY = yPos;
}

void SceneGraph::addChild(NodeRef node) {
   children.push_back(node);
}

void SceneGraph::tick(const double dt) {
   // Camera motion
   if (forward) {
      camera.fly(dt);
   }
   if (backward) {
      camera.fly(-dt);
   }
   if (right) {
      camera.strafe(dt);
   }
   if (left) {
      camera.strafe(-dt);
   }

   // Tick each child
   for (NodeRef child : children) {
      child->tick(dt);
   }
}

NodeRef SceneGraph::findNodeByName(const std::string &name) {
   NodeRef node(nullptr);

   for (NodeRef child : children) {
      // If a direct child matches, return it.
      if (child->getName() == name) {
         return child;
      }

      // If the child does not match, recursively check its children.
      node = child->findNodeByName(name);
      if (node) {
         return node;
      }
   }

   return node;
}
