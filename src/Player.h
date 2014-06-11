#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "InputListener.h"

class Corona;
class Magus;

class Player : public Character, public InputListener {
protected:
   static const float MAX_HEALTH;
   static const float AURA_SCALE;
   static const float MIN_AURA_SIZE;
   static const float ATTACK_POWER;
   static const float WALK_SPEED;
   static const float JUMP_FORCE;
   static const float JUSTITIA_HEALTH_REMOVAL;

   SPtr<Geometry> aura;

   bool wantsToGoLeft, wantsToGoRight, wantsToJump, wantsToAttack;
   double lastMouseX, lastMouseY;
   float invincibilityTime;

public:
   static const float BASE_HEALTH;
   static const std::string CLASS_NAME;

   Player(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
   ~Player();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   /**
    * Draws the geometry in the scene.
    */
   virtual void draw(const RenderData &renderData);

   virtual void onKeyEvent(int key, int action);

   virtual void onMouseButtonEvent(int button, int action);

   virtual void onMouseMotionEvent(double xPos, double yPos);

   virtual void tick(const float dt);

   virtual void setInvincibilityTime(float time);

   virtual void setHealth(float health);

   void resetInputState() {
      wantsToGoLeft = wantsToGoRight = wantsToJump = wantsToAttack = false;
   }

   void forceSetHealth(float health);

   float getAuraRadius();

   bool isInvincible();

   void unmarkForRemoval();

#include "CollisionsBoilerplateH.h"
};

#endif
