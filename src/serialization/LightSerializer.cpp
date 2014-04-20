#include "LightSerializer.h"
#include "Serializer.h"
#include "../engine/IOUtils.h"

#include <memory>

namespace LightSerializer {

LightRef load(const std::string &jsonFileName) {
   Json::Value root = IOUtils::readJsonFile(Light::JSON_FOLDER_PATH + jsonFileName);

   Serializer::check(root, "position", "Light");
   Json::Value posValue = root["position"];

   Serializer::check(posValue, "x", "Light");
   Serializer::check(posValue, "y", "Light");
   Serializer::check(posValue, "z", "Light");
   float xPos = posValue["x"].asFloat();
   float yPos = posValue["y"].asFloat();
   float zPos = posValue["z"].asFloat();
   glm::vec3 position(xPos, yPos, zPos);

   Serializer::check(root, "color", "Light");
   Json::Value colorValue = root["color"];

   Serializer::check(colorValue, "r", "Light");
   Serializer::check(colorValue, "g", "Light");
   Serializer::check(colorValue, "b", "Light");
   float r = colorValue["r"].asFloat();
   float g = colorValue["g"].asFloat();
   float b = colorValue["b"].asFloat();
   glm::vec3 color(r, g, b);

   Serializer::check(root, "constFalloff", "Light");
   Serializer::check(root, "linearFalloff", "Light");
   Serializer::check(root, "squareFalloff", "Light");
   float constFalloff = root["constFalloff"].asFloat();
   float linearFalloff = root["linearFalloff"].asFloat();
   float squareFalloff = root["squareFalloff"].asFloat();

   return LightRef(std::make_shared<Light>(jsonFileName, position, color, constFalloff, linearFalloff, squareFalloff));
}

} // namespace LightSerializer
