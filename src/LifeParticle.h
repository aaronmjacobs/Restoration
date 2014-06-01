#ifndef LIFE_PARTICLE_H
#define LIFE_PARTICLE_H

#include "Particle.h"

class Player;

class LifeParticle : public Particle {
protected:
   static const float MAX_FOLLOW_SPEED;
   float timeAlive;
   WPtr<Player> player;

public:
   static const std::string CLASS_NAME;

   static void createEffect(SPtr<Scene> scene, glm::vec3 position, glm::vec3 velocity, float size, int numParts, float duration, float spread);

   LifeParticle(SPtr<Scene> scene, const std::string &name = "");
   virtual ~LifeParticle();

   virtual void tick(const float dt);

};

#endif
