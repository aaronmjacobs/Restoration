#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "InputListener.h"

class Corona;
class Magus;

class Player : public Character, public InputListener {
protected:
   static const float BASE_HEALTH;
   static const float MAX_HEALTH;
   static const float AURA_SCALE;
   static const float ATTACK_POWER;
   static const float WALK_SPEED;
   static const float JUMP_FORCE;
   static float INVINC_FRAMES;

   SPtr<Geometry> aura;

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

   /**
    * Draws the geometry in the scene.
    */
   virtual void draw(const RenderData &renderData);

   virtual void onKeyEvent(int key, int action);

   virtual void onMouseButtonEvent(int button, int action);

   virtual void onMouseMotionEvent(double xPos, double yPos);

   virtual void tick(const float dt);

   virtual float getInvFrames();

   virtual void setInvFrames(float time);

   virtual void setHealth(float health);

   float getAuraRadius();

#include "CollisionsBoilerplateH.h"
};

#endif
