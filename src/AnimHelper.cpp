#include "AnimHelper.h"
#include "FancyAssert.h"

#include <random>

namespace {

std::default_random_engine generator;

float bezierMatrixArray[16] = {
   -1.0f, 3.0f, -3.0f, 1.0f,
   3.0f, -6.0f, 3.0f, 0.0f,
   -3.0f, 3.0f, 0.0f, 0.0f,
   1.0f, 0.0f, 0.0f, 0.0f
};

glm::mat4 bezierMatrix = glm::make_mat4(bezierMatrixArray);

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

glm::vec3 cubicBezier(float time, glm::vec3 controlOne, glm::vec3 controlTwo, glm::vec3 controlThree, glm::vec3 controlFour) {
   glm::vec4 timeVector = glm::vec4(time * time * time, time * time, time, 1.0f);
   glm::mat4x3 controlMatrix = glm::mat4x3(controlOne, controlTwo, controlThree, controlFour);

   return controlMatrix * bezierMatrix * timeVector;
}

glm::vec3 catmulRom(std::vector<glm::vec3> controlPoints, float time) {
   ASSERT(!controlPoints.empty(), "Must have at least 1 control point");

   float matrixArray[16] = {
      -0.5f, 1.5f, -1.5f, 0.5f,
      1.0f, -2.5f, 2.0f, -0.5f,
      -0.5f, 0.0f, 0.5f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f
   };
   glm::mat4 catmulRomMatrix = glm::make_mat4(matrixArray);

   time *= controlPoints.size() - 1;
   int i = 0;
   while (time > 1.0f) {
      time -= 1.0f;
      ++i;
   }

   glm::vec4 timeVector = glm::vec4(time * time * time, time * time, time, 1.0f);

   int first, second, third, fourth;
   if (i <= 0) {
      first = 0;
   } else {
      first = i - 1;
   }
   second = i;
   third = i + 1;
   if (i >= controlPoints.size() - 2) {
      fourth = i + 1;
   } else {
      fourth = i + 2;
   }

   glm::mat4x3 controlMatrix(controlPoints[first], controlPoints[second], controlPoints[third], controlPoints[fourth]);
      
   return controlMatrix * catmulRomMatrix * timeVector;
}

} // namespace AnimHelper