#ifndef LIGHT_H
#define LIGHT_H

#include "GLMIncludes.h"
#include "ShaderProgram.h"

#include <memory>

class Light;
typedef std::shared_ptr<Light> LightRef;

/**
 * A light in the scene.
 */
class Light {
private:
   /**
    * Maximum number of lights allowed per draw call (as set in shader).
    */
   const static unsigned int MAX_LIGHTS = 10;

   /**
    * Position of the light.
    */
   glm::vec3 position;

   /**
    * Color of the light.
    */
   glm::vec3 color;

   /**
    * The constant, linear, and square light distance falloff values.
    */
   float constFalloff, linearFalloff, squareFalloff;

public:
   /**
    * Constructs a light at the given position, with the given color and falloff values.
    */
   Light(glm::vec3 position, glm::vec3 color, float constFalloff, float linearFalloff, float squareFalloff);
   
   /**
    * Does cleanup (currnetly nothing!).
    */
   virtual ~Light();

   /**
    * Draws the light for the given shader and index.
    */
   void draw(ShaderProgramRef program, const unsigned int lightIndex);
};

#endif
