#ifndef LIGHT_H
#define LIGHT_H

#include "SceneObject.h"

class Scene;
class ShaderProgram;

class Light : public SceneObject {
protected:
   /**
    * Maximum number of lights allowed per draw call (as set in shader).
    */
   const static unsigned int MAX_LIGHTS = 10;

   /**
    * Color of the light.
    */
   glm::vec3 color;

   /**
    * The constant, linear, and square light distance falloff values.
    */
   float constFalloff, linearFalloff, squareFalloff;

public:
   static const std::string CLASS_NAME;

   /**
    * Constructs a light with the given color and falloff values.
    */
   Light(SPtr<Scene> const scene, glm::vec3 color, float constFalloff, float linearFalloff, float squareFalloff, const std::string &name = "");

   /**
    * Does cleanup.
    */
   virtual ~Light();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   /**
    * Draws the light for the given shader and index.
    */
   void draw(ShaderProgram &program, const unsigned int lightIndex);

   virtual void draw();

   /**
    * Steps |dt| seconds through time.
    */
   virtual void tick(const float dt);
};

#endif
