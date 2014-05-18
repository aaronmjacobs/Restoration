#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include "BoundingBox.h"
#include "GLMIncludes.h"
#include "RenderData.h"
#include "RenderState.h"
#include "Serializable.h"
#include "TickListener.h"
#include "Types.h"

#include <string>

class Scene;

class SceneObject : public Serializable, public TickListener {
protected:
   WPtr<Scene> const scene;
   const std::string name;
   glm::vec3 position;
   glm::quat orientation;
   glm::vec3 scale;
   BoundingBox bounds;
   unsigned int renderState;
   bool markedForRemoval;

public:
   static const std::string CLASS_NAME;

   SceneObject(SPtr<Scene> const scene, const std::string &name = "", const BoundingBox bounds = BoundingBox());

   virtual ~SceneObject();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   void setScene(SPtr<Scene> const scene);

   const std::string& getName() {
      return name;
   }

   glm::vec3 getPosition();

   glm::quat getOrientation();

   glm::vec3 getScale();

   BoundingBox getBounds() const;

   void setPosition(const glm::vec3 &position);

   void setOrientation(const glm::quat &orientation);

   void setScale(const glm::vec3 &scale);

   void translateBy(const glm::vec3 &trans);

   void rotateBy(const glm::quat &rot);

   void scaleBy(const glm::vec3 &scale);

   void setRenderState(unsigned int state);

   void enableRenderState(unsigned int state);

   void disableRenderState(unsigned int state);

   bool shouldBeRemoved();

   void markForRemoval();

   virtual void draw(const RenderData &renderData) = 0;
};

#endif
