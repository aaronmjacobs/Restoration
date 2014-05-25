#ifndef PARTICLE_H
#define PARTICLE_H

#include "Geometry.h"

class Particle : public Geometry {
protected:
   static SPtr<Model> particleModel;

   glm::vec3 velocity, acceleration;
   double endTime;

public:
   static const std::string CLASS_NAME;

   static void initialize(SPtr<Scene> scene);

   /* Creates numParts particles with position, velocity, duration(seconds), spread(random component in all directions), gravity (or not), and size. */
   static void createEffect(SPtr<Scene> scene, glm::vec3 position, glm::vec3 velocity, bool gravityOn, float size, int numParts, double duration, float spread);

   Particle(SPtr<Scene> scene, const std::string &name = "");
   virtual ~Particle();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   virtual void tick(const float dt);
};

#endif
