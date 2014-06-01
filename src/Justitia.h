// Player's Vis

#ifndef JUSTITIA_H
#define JUSTITIA_H

#include "Vis.h"

class Justitia : public Vis {
protected:
   static const int ATTACK_POWER;
   float lifeTime;

public:
   static const std::string CLASS_NAME;

   Justitia(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
   virtual ~Justitia();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   /**
    * Draws the geometry in the scene.
    */
   virtual void draw(const RenderData &renderData);

   virtual void tick(const float dt);

#include "CollisionsBoilerplateH.h"
};

#endif
