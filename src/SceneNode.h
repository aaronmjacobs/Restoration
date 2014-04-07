#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <list>
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
   SceneGraph *graph;
   std::list<NodeRef> children;

public:
   SceneNode(SceneGraph *graph, const std::string &name);
   virtual ~SceneNode();
   std::string getName() const {
      return name;
   }
   std::list<NodeRef> getChildren() {
      return children;
   }
   NodeRef findNodeByName(const std::string &name);
   virtual void draw() = 0;
   virtual void tick() = 0;
};

#endif