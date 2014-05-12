#ifndef FOLLOW_GEOMETRY_H
#define FOLLOW_GEOMETRY_H

#include "Geometry.h"

class FollowGeometry : public Geometry {
protected:
   WPtr<SceneObject> target;

public:
   static const std::string CLASS_NAME;

   /**
    * Constructs a geometry node for the given scene with the given name (unique) and model.
    */
   FollowGeometry(SPtr<Scene> scene, SPtr<Model> model, SPtr<SceneObject> target, const std::string &name = "");

   /**
    * Does cleanup.
    */
   virtual ~FollowGeometry();

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
   virtual void draw(unsigned int renderState);

   virtual void tick(const float dt);
};

#endif
