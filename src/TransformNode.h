#ifndef TRANSFORM_NODE_H
#define TRANSFORM_NODE_H

#include "SceneNode.h"

class TransformNode : public SceneNode {
public:
   TransformNode(SceneGraph *scene, const std::string &name);
   ~TransformNode();
   void tick(const double dt);
   void draw(MatrixStack *matrixStack);
};

#endif