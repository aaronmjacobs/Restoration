#ifndef ENEMYSHOOTER_H
#define ENEMYSHOOTER_H

#include "Enemy.h"

#include <memory>

class EnemyShooter;
typedef std::shared_ptr<EnemyShooter> EnemyShooterRef;

/**
* An Enemy that shoots the Player in the scene that can be interacted with.
*/
class EnemyShooter : public Enemy {
public:
   /**
   * The X Movement range of an enemy
   */
   int movementXRange = 5;
   
   /**
   * The Y Movement range of an enemy
   */
   int movementYRange = 0;
   
protected:
   void attack();
   
   void tick(const float dt);

private:
   /**
   * Moves an enemy shooter based on the dt of the tick function
   * Overrides PhysicalObjects move
   */
   void move(const float dt);


};

#endif
