#include "FancyAssert.h"
#include "Light.h"
#include "Scene.h"
#include "ShaderProgram.h"

#include <sstream>

const std::string Light::CLASS_NAME = "Light";

Light::Light(SPtr<Scene> const scene, glm::vec3 color, float constFalloff, float linearFalloff, float squareFalloff, const std::string &name)
   : SceneObject(scene, name), color(color), constFalloff(constFalloff), linearFalloff(linearFalloff), squareFalloff(squareFalloff) {
}

Light::~Light() {
}

Json::Value Light::serialize() const {
   Json::Value root = SceneObject::serialize();

   root["@class"] = CLASS_NAME;

   Json::Value colorVal;
   colorVal["r"] = color.r;
   colorVal["g"] = color.g;
   colorVal["b"] = color.b;
   root["color"] = colorVal;

   root["constFalloff"] = constFalloff;
   root["linearFalloff"] = linearFalloff;
   root["squareFalloff"] = squareFalloff;

   return root;
}

void Light::draw(ShaderProgram &program, const unsigned int lightIndex) {
   // Make sure we're not trying to draw more lights than the shader can support
   ASSERT(lightIndex < MAX_LIGHTS, "Light index (%u) >= MAX_LIGHTS (%u)", lightIndex, MAX_LIGHTS);

   // Set the uniforms for the light index
   std::stringstream ss;
   ss << "uLights[" << lightIndex << "].";
   std::string lightName = ss.str();

   GLint uLightPos = program.getUniform(lightName + "position");
   GLint uLightColor = program.getUniform(lightName + "color");
   GLint uLightConst = program.getUniform(lightName + "constFalloff");
   GLint uLightLinear = program.getUniform(lightName + "linearFalloff");
   GLint uLightSquare = program.getUniform(lightName + "squareFalloff");

   glUniform3fv(uLightPos, 1, glm::value_ptr(position));
   glUniform3fv(uLightColor, 1, glm::value_ptr(color));
   glUniform1f(uLightConst, constFalloff);
   glUniform1f(uLightLinear, linearFalloff);
   glUniform1f(uLightSquare, squareFalloff);
}

void Light::draw() {
}

void Light::tick(const float dt) {
}
