#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include "Camera.h"
#include "SceneNode.h"

#include <memory>

class SceneGraph;
typedef std::shared_ptr<SceneGraph> SceneGraphRef;

/**
 * A scene, composed of all objects in the scene (in a tree), any
 * transformations, and the camera.
 */
class SceneGraph {
private:
   /**
    * Root nodes of the tree.
    */
   std::list<NodeRef> children;

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
    * Adds a node to the root of the scene.
    */
   void addChild(NodeRef node);

   /**
    * Removes a node from the root of the scene.
    */
   void removeChild(NodeRef node);

   /**
    * Gets the top level nodes of the scene.
    */
   const std::list<NodeRef>& getChildren() {
      return children;
   }

   /**
    * Steps |dt| seconds through time.
    */
   void tick(const float dt);

   /**
    * Searches the tree for the node with the given name. If no node is found,
    * a null reference is returned.
    */
   NodeRef findNodeByName(const std::string &name);
};

#endif
