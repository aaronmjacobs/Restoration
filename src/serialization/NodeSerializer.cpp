#include "NodeSerializer.h"
#include "Serializer.h"
#include "../engine/IOUtils.h"

#include <memory>

namespace NodeSerializer {

NodeRef load(const std::string &jsonFileName, Scene *scene) {
   return deserialize(IOUtils::readJsonFile(GeometryNode::JSON_FOLDER_PATH + jsonFileName), scene);
}

NodeRef deserialize(const Json::Value &root, Scene *scene) {
   Serializer::check(root, "@class", "SceneNode");
   std::string className = root["@class"].asString();

   // Check which material it matches
   if (className == GeometryNode::CLASS_NAME) {
      return GeometryNodeSerializer::deserialize(root, scene);
   } else if (className == TransformNode::CLASS_NAME) {
      return TransformNodeSerializer::deserialize(root, scene);
   } else if (className == Platform::CLASS_NAME) {
      return PlatformSerializer::deserialize(root, scene);
   }

   ASSERT(false, "Invalid class name: %s", className.c_str());

   return NodeRef();
}

} // namespace NodeSerializer
