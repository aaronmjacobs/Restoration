#include "FancyAssert.h"
#include "Geometry.h"
#include "GeometryDeserializer.h"
#include "ModelDeserializer.h"
#include "Types.h"

namespace GeometryDeserializer {

SPtr<Geometry> deserialize(const Json::Value &root, SPtr<Scene> const scene) {
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

   // Geometry

   // Model
   SPtr<Model> model = ModelDeserializer::deserialize(root["model"], scene);

   SPtr<Geometry> geometry = std::make_shared<Geometry>(scene, model, name);
   geometry->setPosition(position);
   geometry->setOrientation(orientation);
   geometry->setScale(scale);

   return geometry;
}

} // namespace GeometryDeserializer
