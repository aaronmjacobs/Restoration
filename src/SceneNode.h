#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include "GLMIncludes.h"

#include <list>
#include <memory>
#include <string>

class SceneGraph;
class SceneNode;

typedef std::shared_ptr<const SceneNode> NodeRef;

class SceneNode {
private:
   glm::vec3 position;
   glm::quat rotation;
   glm::vec3 scale;
   bool visible;
   std::string name;
   SceneGraph *graph;
   std::list<SceneNode> children;

public:
   SceneNode(SceneGraph *graph, const std::string &name);
   virtual ~SceneNode();
   std::string getName() const {
      return name;
   }
   virtual void draw();
   virtual void tick();
};

#endif