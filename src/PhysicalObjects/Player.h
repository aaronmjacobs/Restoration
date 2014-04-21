#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "../engine/InputListener.h"

#include <memory>

class Player;
class Platform;
typedef std::shared_ptr<Player> PlayerRef;

class Player : public Character, public InputListener{
private:

   //bools to be set by input functions and used in tick
   bool wKey = false, aKey = false, sKey = false, dKey = false, jump = false, click = false;
   bool onGround = false;

   //set character's movement speed
   const float SPEED = 5.0f;

   glm::vec3 velocity;
   glm::vec3 acceleration;

public:
   /**
   * Constructs a character for the given scene with the given name (unique) and model.
   */
   Player(Scene *scene, const std::string &jsonFileName, const std::string &name, ModelRef model);

   /**
   * Does cleanup (currently nothing!).
   */
   virtual ~Player();

   void setVelocity(glm::vec3 vel) {
      velocity = vel;
   }

   glm::vec3 getVelocity() {
      return velocity;
   }

   void setOnGround() {
      onGround = true;
   }

   //function for key input
   virtual void onKeyEvent(int key, int action);

   //function for mouse input
   virtual void onMouseButtonEvent(int button, int action);

   virtual void onMouseMotionEvent(double xPos, double yPos);

   //run on time tick
   virtual void tick(const float dt);

   virtual void move(glm::vec3 dir);

   virtual void attack();

   // Collision stuff
   virtual void collideWith(PhysicalObject *physObj);
   virtual void collideWith(Player *player);
   virtual void collideWith(Platform *platform);
};

#endif
