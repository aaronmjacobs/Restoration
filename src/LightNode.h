#ifndef LIGHT_NODE_H
#define LIGHT_NODE_H

#include "Light.h"
#include "SceneNode.h"

class LightNode : public SceneNode {
private:
   LightRef light;

public:
   LightNode(SceneGraph *scene, const std::string &name, LightRef light);
   ~LightNode();
};

#endif