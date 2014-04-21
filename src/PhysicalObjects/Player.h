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

   //set character's movement speed
   const float SPEED = 5.0f;

public:
   /**
   * Constructs a character for the given scene with the given name (unique) and model.
   */
   Player(Scene *scene, const std::string &jsonFileName, const std::string &name, ModelRef model);

   /**
   * Does cleanup (currently nothing!).
   */
   virtual ~Player();

   //function for key input
   virtual void onKeyEvent(int key, int action);

   //function for mouse input
   virtual void onMouseButtonEvent(int button, int action);

   virtual void onMouseMotionEvent(double xPos, double yPos);

   //run on time tick
   virtual void tick(const float dt);

   virtual void move(glm::vec3 dir);

   virtual void attack();
};

#endif
