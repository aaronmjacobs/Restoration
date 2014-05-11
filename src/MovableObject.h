#ifndef MOVABLE_OBJECT_H
#define MOVABLE_OBJECT_H

#include "PhysicalObject.h"

class MovableObject : public PhysicalObject {
protected:
   const float GRAVITY = -9.8f;
   glm::vec3 velocity, acceleration;

public:
   static const std::string CLASS_NAME;

   MovableObject(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
   virtual ~MovableObject();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   glm::vec3 getVelocity();
   glm::vec3 getAcceleration();
   void setVelocity(const glm::vec3 &vel);
   void setAcceleration(const glm::vec3 &acc);

   virtual void tick(const float dt);
};

#endif
