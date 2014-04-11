#include "Light.h"

Light::Light(glm::vec3 color, float constFalloff, float linearFalloff, float squareFalloff) {
   this->color = color;
   this->constFalloff = constFalloff;
   this->linearFalloff = linearFalloff;
   this->squareFalloff = squareFalloff;
}

Light::~Light() {
   
}