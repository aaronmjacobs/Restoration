#ifndef PARTICLE_H
#define PARTICLE_H

#include "Geometry.h"

class Particle : public Geometry {
protected:
   static SPtr<Model> particleModel;

   glm::vec3 velocity, acceleration;

public:
   static const std::string CLASS_NAME;

   static void initialize(SPtr<Scene> scene);

   Particle(SPtr<Scene> scene, const std::string &name = "");
   virtual ~Particle();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   virtual void tick(const float dt);
};

#endif
