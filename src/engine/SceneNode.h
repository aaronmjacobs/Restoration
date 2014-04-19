#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include "GLMIncludes.h"
#include "MatrixStack.h"
#include "TickListener.h"

#include <list>
#include <memory>
#include <string>

class Scene;
class SceneNode;
typedef std::shared_ptr<SceneNode> NodeRef;

/**
 * A node in the scene.
 */
class SceneNode : public TickListener {
protected:
    /**
    * A unique name for the node.
    */
   const std::string name;

   /**
    * The position of the node.
    */
   glm::vec3 position;

   /**
    * The orientation of the node.
    */
   glm::quat orientation;

   /**
    * The scale of the node.
    */
   glm::vec3 scale;

   /**
    * The parent of this node (may be null).
    */
   NodeRef parent;

   /**
    * The child nodes of the node.
    */
   std::list<NodeRef> children;

public:
   /**
    * Constructs a node with the given name.
    */
   SceneNode(const std::string &name);

   /**
    * Does cleanup.
    */
   virtual ~SceneNode();

   /**
    * Gets the parent node of this node (may be null).
    */
   NodeRef getParent() {
      return parent;
   }

   /**
    * Sets the parent node of this node.
    */
   void setParent(NodeRef parent) {
      this->parent = parent;
   }

   /**
    * Gets the name of the node.
    */
   const std::string& getName() const {
      return name;
   }

   /**
    * Gets the children of the node.
    */
   const std::list<NodeRef>& getChildren() {
      return children;
   }

   /**
    * Adds a child node to the node.
    */
   void addChild(NodeRef node);

   /**
    * Removes a child node from the node.
    */
   void removeChild(NodeRef node);

   /**
    * Searches the tree for the node with the given name. If no node is found,
    * a null reference is returned.
    */
   NodeRef findNodeByName(const std::string &name);

   /**
    * Translates the node by the given vector.
    */
   void translateBy(glm::vec3 trans);

   /**
    * Rotates the node by the given quaternion.
    */
   void rotateBy(glm::quat rot);

   /**
    * Scales the node by the given vector.
    */
   void scaleBy(glm::vec3 scale);

   /**
    * Steps |dt| seconds through time.
    */
   virtual void tick(const float dt);

   /**
    * Draws the node (and all children) with the given model matrix stack.
    */
   virtual void draw(MatrixStack *modelMatrixStack) = 0;
};

#endif
