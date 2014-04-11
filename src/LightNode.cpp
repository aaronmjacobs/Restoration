#include "LightNode.h"

LightNode::LightNode(SceneGraph *scene, const std::string &name, LightRef light)
   : SceneNode(scene, name) {
   this->light = light;
}

LightNode::~LightNode() {

}