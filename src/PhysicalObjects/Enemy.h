#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "../engine/Scene.h"

#include <list>

class Enemy;
typedef std::shared_ptr<Enemy> EnemyRef;

/**
* A character (NPC or PC) in the scene that can be interacted with.
*/
class Enemy : public Character {
public:
   static std::list<Enemy*> allEnemies;
   /**
   * Constructs an enemy for the given scene with the given name (unique) and model.
   */
   Enemy(Scene *scene, const std::string &jsonFileName, const std::string &name, ModelRef model);

   /**
   * Does cleanup (currently nothing!).
   */
   virtual ~Enemy();

   bool alive;

   void die();

protected:
   /**
   * How secure the NPC feels with the human near it.
   * Varying degrees of security from different things.
   * This will be used to specify a finite state machine.
   * EX : Line of Sight == Mild insecurity.
   * EX : Last one in the area == Highest insecurity.
   */
   int security;

   int excitement;

   bool beenShot;
   
   bool seePlayer;
private:
   /**
   * Update the security based on the type of enemy.
   * Maybe the melee enemy reacts differently from the shooter
   * enemy when isolated.
   */
   virtual void updateStatus(Player playerRef);

   /**
   * Update the state based on the security. Get information about the 
   * player via PlayerRef so that we can do interesting things with the AI.
   */
   virtual void updateState(Player playerRef);

   virtual void tick(const float dt);

   virtual void move(glm::vec3 dir);

   virtual void attack();
};

#endif
