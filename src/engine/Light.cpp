#include "FancyAssert.h"
#include "Light.h"

#include <sstream>

const std::string Light::JSON_FOLDER_PATH = "data/light/";

Light::Light(const std::string &jsonFileName, glm::vec3 position, glm::vec3 color, float constFalloff, float linearFalloff, float squareFalloff)
   : Serializable(jsonFileName) {
   this->position = position;
   this->color = color;
   this->constFalloff = constFalloff;
   this->linearFalloff = linearFalloff;
   this->squareFalloff = squareFalloff;
}

Light::~Light() {
}

Json::Value Light::serialize() const {
   Json::Value root;

   Json::Value posValue;
   posValue["x"] = position.x;
   posValue["y"] = position.y;
   posValue["z"] = position.z;
   root["position"] = posValue;

   Json::Value colorValue;
   colorValue["r"] = color.r;
   colorValue["g"] = color.g;
   colorValue["b"] = color.b;
   root["color"] = colorValue;

   root["constFalloff"] = constFalloff;
   root["linearFalloff"] = linearFalloff;
   root["squareFalloff"] = squareFalloff;

   return root;
}

void Light::draw(ShaderProgramRef program, const unsigned int lightIndex) {
   // Make sure we're not trying to draw more lights than the shader can support
   ASSERT(lightIndex < MAX_LIGHTS, "Light index (%u) >= MAX_LIGHTS (%u)", lightIndex, MAX_LIGHTS);

   // Set the uniforms for the light index
   std::stringstream ss;
   ss << "uLights[" << lightIndex << "].";
   std::string lightName = ss.str();

   GLint uLightPos = program->getUniform(lightName + "position");
   GLint uLightColor = program->getUniform(lightName + "color");
   GLint uLightConst = program->getUniform(lightName + "constFalloff");
   GLint uLightLinear = program->getUniform(lightName + "linearFalloff");
   GLint uLightSquare = program->getUniform(lightName + "squareFalloff");

   glUniform3fv(uLightPos, 1, glm::value_ptr(position));
   glUniform3fv(uLightColor, 1, glm::value_ptr(color));
   glUniform1f(uLightConst, constFalloff);
   glUniform1f(uLightLinear, linearFalloff);
   glUniform1f(uLightSquare, squareFalloff);
}
