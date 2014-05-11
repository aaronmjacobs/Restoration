#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "SceneObject.h"

class MatrixStack;
class Model;

/**
 * A piece of geometry in the scene.
 */
class Geometry : public SceneObject {
protected:
   /**
    * Reference to the model drawn by this node.
    */
   SPtr<Model> model;

public:
   static const std::string CLASS_NAME;

   /**
    * Constructs a geometry node for the given scene with the given name (unique) and model.
    */
   Geometry(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");

   /**
    * Does cleanup.
    */
   virtual ~Geometry();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   /**
    * Gets the model of the geometry.
    */
   SPtr<Model> getModel();

   /**
    * Draws the geometry in the scene.
    */
   virtual void draw();
};

#endif
