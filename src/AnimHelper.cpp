#include "AnimHelper.h"
#include "FancyAssert.h"

#include <random>

namespace {

std::default_random_engine generator;

} // namespace

namespace AnimHelper {

glm::vec3 randomLinear(float min, float max) {
   ASSERT(max >= min, "Max can not be less than min: [%f, %f]", min, max);
   std::uniform_real_distribution<float> distribution(min, max);
   return glm::vec3(distribution(generator), distribution(generator), distribution(generator));
}

glm::vec3 randomSpherical(float radius) {
   ASSERT(radius >= 0.0f, "Negative radius not allowed: %f", radius);
   std::uniform_real_distribution<float> radialDistribution(0.0f, radius);
   std::uniform_real_distribution<float> angleDistribution(0.0f, glm::pi<float>() * 2.0f);

   float r = radialDistribution(generator);
   float theta = angleDistribution(generator);
   float phi = angleDistribution(generator);

   return glm::vec3(r * glm::cos(theta) * glm::sin(phi),
                    r * glm::sin(theta) * glm::sin(phi),
                    r * glm::cos(phi));
}

float random(float min, float max) {
   ASSERT(max >= min, "Max can not be less than min: [%f, %f]", min, max);
   std::uniform_real_distribution<float> distribution(min, max);
   return distribution(generator);
}

} // namespace AnimHelper