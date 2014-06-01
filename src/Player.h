#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "InputListener.h"

class Corona;
class Magus;

class Player : public Character, public InputListener {
protected:
   static const int BASE_HEALTH;
   static const float WALK_SPEED;
   static const float JUMP_FORCE;
   static float INVINC_FRAMES;

   SPtr<Geometry> aura;
   float auraRadius;

   bool wantsToGoLeft, wantsToGoRight, wantsToJump, wantsToAttack;
   double lastMouseX, lastMouseY;

public:
   static const std::string CLASS_NAME;

   Player(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
   ~Player();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   virtual void onKeyEvent(int key, int action);

   virtual void onMouseButtonEvent(int button, int action);

   virtual void onMouseMotionEvent(double xPos, double yPos);

   virtual void tick(const float dt);

   virtual float getInvFrames();

   virtual void setInvFrames(float time);

   virtual void setHealth(int health);

   float getAuraRadius();
   void growAura(float amount);

#include "CollisionsBoilerplateH.h"
};

#endif
