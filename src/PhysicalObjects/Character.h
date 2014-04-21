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
   * Constructs a character for the given scene with the given name (unique) and model.
   */
   Character(Scene *scene, const std::string &jsonFileName, const std::string &name, ModelRef model);

   /**
   * Does cleanup (currently nothing!).
   */
   virtual ~Character();

   /**
   * Get the health of the character for traps and other physical object
   * that may not extend character.
   */
   int getHealth();

   void setVelocity(glm::vec3 vel) {
      velocity = vel;
   }

   glm::vec3 getVelocity() {
      return velocity;
   }

   void setOnGround() {
      onGround = true;
   }

protected:
   /**
   * Health value for the character
   */
   int health;

   glm::vec3 velocity;
   glm::vec3 acceleration;
   bool onGround = false;

   /**
   * Lose health function for character based on some integer health lost.
   */
   virtual void loseHealth(int harm);

   /**
   * Regenerate health for character based on some integer health gained.
   */
   virtual void regenHealth(int heal);

   /**
   * Attack with the character.
   */
   virtual void attack() = 0;
};

#endif
