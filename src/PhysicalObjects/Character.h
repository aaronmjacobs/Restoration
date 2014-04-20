#ifndef CHARACTER_H
#define CHARACTER_H

#include "PhysicalObject.h"

class Character;
typedef std::shared_ptr<Character> CharacterRef;

/**
* A character (NPC or PC) in the scene that can be interacted with.
*/
class Character : public PhysicalObject {
public:

   /**
   * Get the health of the character for traps and other physical object
   * that may not extend character.
   */
   int getHealth();

protected:
   /**
   * Health value for the character
   */
   int health;

   /**
   * Lose health function for character based on some integer health lost.
   */
   virtual void loseHealth(int harm) = 0;

   /**
   * Regenerate health for character based on some integer health gained.
   */
   virtual void regenHealth(int heal) = 0;

   /**
   * Attack with the character.
   */
   virtual void attack() = 0;
};

#endif
