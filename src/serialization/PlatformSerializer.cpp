#include "PlatformSerializer.h"
#include "Serializer.h"
#include "../engine/IOUtils.h"

#include <memory>

namespace PlatformSerializer {

PlatformRef load(const std::string &jsonFileName, Scene *scene) {
   return deserialize(IOUtils::readJsonFile(Platform::JSON_FOLDER_PATH + jsonFileName), scene);
}

PlatformRef deserialize(const Json::Value &root, Scene *scene) {
   // SceneNode items

   // Name
   Serializer::check(root, "name", "Platform");
   std::string name = root["name"].asString();

   // Position
   Serializer::check(root, "position", "Platform");
   Json::Value posValue = root["position"];
   Serializer::check(posValue, "x", "Platform");
   Serializer::check(posValue, "y", "Platform");
   Serializer::check(posValue, "z", "Platform");
   float xPos = posValue["x"].asFloat();
   float yPos = posValue["y"].asFloat();
   float zPos = posValue["z"].asFloat();
   glm::vec3 position(xPos, yPos, zPos);

   // Orientation
   Serializer::check(root, "orientation", "Platform");
   Json::Value oriValue = root["orientation"];
   Serializer::check(oriValue, "w", "Platform");
   Serializer::check(oriValue, "x", "Platform");
   Serializer::check(oriValue, "y", "Platform");
   Serializer::check(oriValue, "z", "Platform");
   float wOri = oriValue["w"].asFloat();
   float xOri = oriValue["x"].asFloat();
   float yOri = oriValue["y"].asFloat();
   float zOri = oriValue["z"].asFloat();
   glm::quat orientation(wOri, xOri, yOri, zOri);

   // Scale
   Serializer::check(root, "scale", "Platform");
   Json::Value scaleValue = root["scale"];
   Serializer::check(scaleValue, "x", "Platform");
   Serializer::check(scaleValue, "y", "Platform");
   Serializer::check(scaleValue, "z", "Platform");
   float xScale = scaleValue["x"].asFloat();
   float yScale = scaleValue["y"].asFloat();
   float zScale = scaleValue["z"].asFloat();
   glm::vec3 scale(xScale, yScale, zScale);

   // GeometryNode items
   Serializer::check(root, "model", "Platform");
   std::string modelJsonName = root["model"].asString();
   ModelRef model = ModelSerializer::load(modelJsonName, scene);

   // Create the node
   PlatformRef node = std::make_shared<Platform>(scene, "TODO", name, model);

   // Set properties
   node->translateBy(position);
   node->rotateBy(orientation);
   node->scaleBy(scale);

   // AABB
   Serializer::check(root, "bounds", "Platform");
   Json::Value boundsVal = root["bounds"];
   AxisAlignedBoundingBox bounds;
   bounds.xMin = boundsVal["xMin"].asFloat();
   bounds.xMax = boundsVal["xMax"].asFloat();
   bounds.yMin = boundsVal["yMin"].asFloat();
   bounds.yMax = boundsVal["yMax"].asFloat();
   node->setBounds(bounds);

   // Set up children
   Serializer::check(root, "children", "Platform");
   Json::Value childrenValue = root["children"];
   ASSERT(childrenValue.isArray(), "children should be an array");
   for (int i = 0; i < childrenValue.size(); ++i) {
      NodeRef childNode = NodeSerializer::deserialize(childrenValue[i], scene);

      node->addChild(childNode);
      childNode->setParent(node);
   }

   return node;
}

} // namespace PlatformSerializer
