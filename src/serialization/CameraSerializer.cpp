#include "CameraSerializer.h"
#include "Serializer.h"
#include "../engine/IOUtils.h"

#include <memory>

namespace CameraSerializer {

CameraRef load(const std::string &jsonFileName) {
   Json::Value root = IOUtils::readJsonFile(Camera::JSON_FOLDER_PATH + jsonFileName);

   Serializer::check(root, "phi", "Camera");
   Json::Value posValue = root["position"];

   Serializer::check(posValue, "x", "Camera");
   Serializer::check(posValue, "y", "Camera");
   Serializer::check(posValue, "z", "Camera");
   float xPos = posValue["x"].asFloat();
   float yPos = posValue["y"].asFloat();
   float zPos = posValue["z"].asFloat();
   glm::vec3 position(xPos, yPos, zPos);

   Serializer::check(root, "phi", "Camera");
   Serializer::check(root, "theta", "Camera");
   float phi = root["phi"].asFloat();
   float theta = root["theta"].asFloat();

   return CameraRef(std::make_shared<Camera>(jsonFileName, position, phi, theta));
}

} // namespace CameraSerializer
