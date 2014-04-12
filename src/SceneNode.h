#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include "GLMIncludes.h"

#include "MatrixStack.h"

#include <list>
#include <memory>
#include <string>

class SceneGraph;
class SceneNode;

typedef std::shared_ptr<SceneNode> NodeRef;

class SceneNode {
private:
   const std::string name;

protected:
   glm::vec3 position;
   glm::quat rotation;
   glm::vec3 scale;
   bool visible;
   SceneGraph *scene;
   NodeRef parent;
   std::list<NodeRef> children;

public:
   SceneNode(SceneGraph *scene, const std::string &name);
   virtual ~SceneNode();
   std::string getName() const {
      return name;
   }
   std::list<NodeRef> getChildren() {
      return children;
   }
   void addChild(NodeRef node) {
      children.push_back(node);
   }
   NodeRef findNodeByName(const std::string &name);
   virtual void tick(const double dt) = 0;
   virtual void draw(MatrixStack *modelMatrixStack) = 0;
};

#endif