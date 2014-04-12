#ifndef LIGHT_H
#define LIGHT_H

#include "GLMIncludes.h"
#include "ShaderProgram.h"

#include <memory>

class Light;
typedef std::shared_ptr<Light> LightRef;

class Light {
private:
   const static unsigned int MAX_LIGHTS = 10;
   glm::vec3 position;
   glm::vec3 color;
   float constFalloff, linearFalloff, squareFalloff;

public:
   Light(glm::vec3 position, glm::vec3 color, float constFalloff, float linearFalloff, float squareFalloff);
   ~Light();
   void draw(ShaderProgramRef program, const unsigned int lightIndex);
};

#endif