#ifndef TRANSFORM_NODE_H
#define TRANSFORM_NODE_H

#include "SceneNode.h"
#include "Serializable.h"

class TransformNode;
typedef std::shared_ptr<TransformNode> TransformNodeRef;

/**
 * A transformation in the scene.
 */
class TransformNode : public SceneNode {
public:
   /**
    * Name of the class (used in deserialization to determine types).
    */
   static const std::string CLASS_NAME;

   /**
    * Constructs a transformation node with the given name.
    */
   TransformNode(Scene *scene, const std::string &jsonFileName, const std::string &name);

   /**
    * Does cleanup.
    */
   virtual ~TransformNode();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

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
