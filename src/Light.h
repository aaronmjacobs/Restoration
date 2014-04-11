#ifndef LIGHT_H
#define LIGHT_H

#include "GLMIncludes.h"

#include <memory>

class Light;
typedef std::shared_ptr<Light> LightRef;

class Light {
private:
   glm::vec3 color;
   float constFalloff, linearFalloff, squareFalloff;

public:
   Light(glm::vec3 color, float constFalloff, float linearFalloff, float squareFalloff);
   ~Light();
};

#endif