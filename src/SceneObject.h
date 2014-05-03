#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include "GLMIncludes.h"
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

public:
   static const std::string CLASS_NAME;

   SceneObject(SPtr<Scene> const scene, const std::string &name = "");

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

   void setPosition(const glm::vec3 &position);

   void setOrientation(const glm::quat &orientation);

   void setScale(const glm::vec3 &scale);

   void translateBy(const glm::vec3 &trans);

   void rotateBy(const glm::quat &rot);

   void scaleBy(const glm::vec3 &scale);

   virtual void draw() = 0;
};

#endif
