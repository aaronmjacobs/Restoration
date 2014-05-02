#include "FancyAssert.h"
#include "Light.h"
#include "LightDeserializer.h"
#include "Types.h"

namespace LightDeserializer {

SPtr<Light> deserialize(const Json::Value &root, SPtr<Scene> const scene) {
   // Scene object

   // Name
   std::string name = root["name"].asString();

   // Position
   glm::vec3 position;
   Json::Value posVal = root["position"];
   position.x = posVal["x"].asFloat();
   position.y = posVal["y"].asFloat();
   position.z = posVal["z"].asFloat();

   // Orientation
   glm::quat orientation;
   Json::Value oriVal = root["orientation"];
   orientation.w = oriVal["w"].asFloat();
   orientation.x = oriVal["x"].asFloat();
   orientation.y = oriVal["y"].asFloat();
   orientation.z = oriVal["z"].asFloat();

   // Scale
   glm::vec3 scale;
   Json::Value scaleVal = root["scale"];
   scale.x = scaleVal["x"].asFloat();
   scale.y = scaleVal["y"].asFloat();
   scale.z = scaleVal["z"].asFloat();

   // Light

   // Color
   glm::vec3 color;
   Json::Value colorVal = root["color"];
   color.r = colorVal["r"].asFloat();
   color.g = colorVal["g"].asFloat();
   color.b = colorVal["b"].asFloat();

   // Falloff
   float constFalloff = root["constFalloff"].asFloat();
   float linearFalloff = root["linearFalloff"].asFloat();
   float squareFalloff = root["squareFalloff"].asFloat();

   SPtr<Light> light = std::make_shared<Light>(scene, color, constFalloff, linearFalloff, squareFalloff, name);
   light->setPosition(position);
   light->setOrientation(orientation);
   light->setScale(scale);

   return light;
}

} // namespace LightDeserializer
