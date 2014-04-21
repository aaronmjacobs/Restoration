#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy;
typedef std::shared_ptr<Enemy> EnemyRef;

/**
* A character (NPC or PC) in the scene that can be interacted with.
*/
class Enemy : public Character {
public:
   /**
   * Constructs an enemy for the given scene with the given name (unique) and model.
   */
   Enemy(const std::string &jsonFileName, const std::string &name, ModelRef model);

   /**
   * Does cleanup (currently nothing!).
   */
   virtual ~Enemy();

protected:
   /**
   * How secure the NPC feels with the human near it.
   * Varying degrees of security from different things.
   * This will be used to specify a finite state machine.
   * EX : Line of Sight == Mild insecurity.
   * EX : Last one in the area == Highest insecurity.
   */
   int security;

   bool beenShot;
   
   bool seePlayer;
private:
   /**
   * Update the security based on the type of enemy.
   * Maybe the melee enemy reacts differently from the shooter
   * enemy when isolated.
   */
   virtual int updateSecurity() = 0;

   /**
   * Update the state based on the security.
   */
   virtual void updateState(int security) = 0;


};

#endif
