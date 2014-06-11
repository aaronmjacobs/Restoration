#ifndef ANIM_HELPER_H
#define ANIM_HELPER_H

#include "GLMIncludes.h"

#include <vector>

namespace AnimHelper {

glm::vec3 randomLinear(float min, float max);
glm::vec3 randomSpherical(float radius);
float random(float min, float max);
glm::vec3 cubicBezier(float time, glm::vec3 controlOne, glm::vec3 controlTwo, glm::vec3 controlThree, glm::vec3 controlFour);
   glm::vec3 catmulRom(std::vector<glm::vec3> controlPoints, float time);

} // namespace AnimHelper

namespace Interpolate {

template<typename T>
T linear(T first, T second, T amount) {
   return first * (1 - amount) + second * amount;
}

template<typename T>
T square(T first, T second, T amount) {
   return first * ((1 - amount) * (1 - amount)) + second * (amount * amount);
}

} // namespace Interpolate

#endif
