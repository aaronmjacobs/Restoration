#include "SceneNode.h"
#include "SceneObject.h"

SceneNode::SceneNode(SPtr<SceneObject> object)
   : object(object) {
}

SceneNode::~SceneNode() {
}
