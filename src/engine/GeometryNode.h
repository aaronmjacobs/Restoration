#ifndef GEOMETRY_NODE_H
#define GEOMETRY_NODE_H

#include "GLIncludes.h"
#include "Model.h"
#include "SceneNode.h"
#include "ShaderProgram.h"

#include <memory>

class GeometryNode;
typedef std::shared_ptr<GeometryNode> GeometryNodeRef;

/**
 * A piece of geometry in the scene.
 */
class GeometryNode : public SceneNode {
private:
   /**
    * Reference to the model drawn by this node.
    */
   ModelRef model;

public:
   /**
    * Constructs a geometry node for the given scene with the given name (unique) and model.
    */
   GeometryNode(SceneGraph *scene, const std::string &name, ModelRef model);

   /**
    * Does cleanup (currently nothing!).
    */
   virtual ~GeometryNode();

   /**
    * Draws the geometry in the scene.
    */
   virtual void draw(MatrixStack *modelMatrixStack);

   /**
    * Steps |dt| seconds through time.
    */
   virtual void tick(const double dt);
};

#endif
