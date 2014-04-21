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
    * Name of the class (used in deserialization to determine types).
    */
   static const std::string CLASS_NAME;

   /**
    * Constructs a geometry node for the given scene with the given name (unique) and model.
    */
   GeometryNode(Scene *scene, const std::string &jsonFileName, const std::string &name, ModelRef model);

   /**
    * Does cleanup (currently nothing!).
    */
   virtual ~GeometryNode();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   /**
    * Gets the model of the geometry.
    */
   ModelRef getModel() {
      return model;
   }

   /**
    * Draws the geometry in the scene.
    */
   virtual void draw(MatrixStack *modelMatrixStack);

   /**
    * Steps |dt| seconds through time.
    */
   virtual void tick(const float dt);
};

#endif
