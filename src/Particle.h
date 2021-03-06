#ifndef PARTICLE_H
#define PARTICLE_H

#include "Geometry.h"

class Particle : public Geometry {
protected:
   static SPtr<Model> particleModel;
   static SPtr<Model> stencilParticleModel;

   glm::vec3 velocity, acceleration;
   float duration;
   float size;

public:
   static const std::string CLASS_NAME;

   static void initialize(SPtr<Scene> scene);

   /* Creates numParts particles with position, velocity, duration(seconds), spread(random component in all directions), gravity (or not), and size. */
   static void createEffect(SPtr<Scene> scene, glm::vec3 position, glm::vec3 velocity, bool gravityOn, float size, int numParts, float duration, float spread, bool stencil);

   Particle(SPtr<Scene> scene, SPtr<Model> model, float size, const std::string &name = "");
   virtual ~Particle();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   virtual void tick(const float dt);
};

#endif
