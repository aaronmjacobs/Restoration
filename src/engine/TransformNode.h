#ifndef TRANSFORM_NODE_H
#define TRANSFORM_NODE_H

#include "SceneNode.h"

/**
 * A transformation in the scene.
 */
class TransformNode : public SceneNode {
public:
   /**
    * Constructs a transformation node with the given name.
    */
   TransformNode(const std::string &name);

   /**
    * Does cleanup.
    */
   virtual ~TransformNode();

   /**
    * Steps |dt| seconds through time.
    */
   virtual void tick(const float dt);

   /**
    * Applies the transformations to the model matrix stack, and draws all
    * children.
    */
   virtual void draw(MatrixStack *modelMatrixStack);
};

#endif
