#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include "Camera.h"
#include "SceneNode.h"

#include <memory>

/**
 * A scene, composed of all objects in the scene (in a tree), any
 * transformations, and the camera.
 */
class SceneGraph {
private:
   /**
    * The camera to view the scene through.
    */
   Camera camera;

   /**
    * Root nodes of the tree.
    */
   std::list<NodeRef> children;

   /**
    * Camera / movement / control state.
    */
   bool forward, backward, left, right;
   bool leftMouse;
   double mouseX, mouseY;

public:
   /**
    * Constructs the scene.
    */
   SceneGraph();

   /**
    * Does cleanup.
    */
   virtual ~SceneGraph();

   /**
    * Handles keyboard events.
    */
   void onKeyEvent(int key, int action);

   /**
    * Handles mouse click events.
    */
   void onMouseEvent(int button, int action);

   /**
    * Handles mouse motion events.
    */
   void onMouseMotionEvent(double xPos, double yPos);

   /**
    * Adds a node to the root of the scene.
    */
   void addChild(NodeRef node);

   /**
    * Gets the top level nodes of the scene.
    */
   const std::list<NodeRef>& getChildren() {
      return children;
   }

   /**
    * Gets a reference to the scene's camera.
    */
   Camera* getCamera() {
      return &camera;
   }

   /**
    * Steps |dt| seconds through time.
    */
   void tick(const double dt);

   /**
    * Searches the tree for the node with the given name. If no node is found,
    * a null reference is returned.
    */
   NodeRef findNodeByName(const std::string &name);
};

#endif
