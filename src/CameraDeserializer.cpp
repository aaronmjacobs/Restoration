#include "FancyAssert.h"
#include "Camera.h"
#include "CameraDeserializer.h"
#include "Types.h"

namespace CameraDeserializer {

SPtr<Camera> deserialize(const Json::Value &root, SPtr<Scene> const scene) {
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

   // Camera

   // Phi, theta
   float phi = root["phi"].asFloat();
   float theta = root["theta"].asFloat();

   SPtr<Camera> camera = std::make_shared<Camera>(scene, name);
   camera->setPosition(position);
   camera->setOrientation(orientation);
   camera->setScale(scale);
   camera->setRotation(phi, theta);

   return camera;
}

} // namespace CameraDeserializer
