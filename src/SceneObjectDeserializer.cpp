#include "Camera.h"
#include "CameraDeserializer.h"
#include "FancyAssert.h"
#include "Geometry.h"
#include "GeometryDeserializer.h"
#include "Light.h"
#include "LightDeserializer.h"
#include "SceneObject.h"
#include "SceneObjectDeserializer.h"
#include "Types.h"

namespace SceneObjectDeserializer {

SPtr<SceneObject> deserialize(const Json::Value &root, SPtr<Scene> const scene) {
   std::string className = root["@class"].asString();

   if (className == Geometry::CLASS_NAME) {
      return GeometryDeserializer::deserialize(root, scene);
   } else if (className == Light::CLASS_NAME) {
      return LightDeserializer::deserialize(root, scene);
   } else if (className == Camera::CLASS_NAME) {
      return CameraDeserializer::deserialize(root, scene);
   }

   ASSERT(false, "Invalid class name for SceneObject: %s", className.c_str());

   return SPtr<SceneObject>();
}

} // namespace SceneObjectDeserializer
