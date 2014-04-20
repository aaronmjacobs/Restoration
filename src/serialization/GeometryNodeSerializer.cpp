#include "GeometryNodeSerializer.h"
#include "Serializer.h"
#include "../engine/IOUtils.h"

#include <memory>

namespace GeometryNodeSerializer {

GeometryNodeRef load(const std::string &jsonFileName, Scene *scene) {
   return deserialize(IOUtils::readJsonFile(GeometryNode::JSON_FOLDER_PATH + jsonFileName), scene);
}

GeometryNodeRef deserialize(const Json::Value &root, Scene *scene) {
   // SceneNode items

   // Name
   Serializer::check(root, "name", "GeometryNode");
   std::string name = root["name"].asString();

   // Position
   Serializer::check(root, "position", "GeometryNode");
   Json::Value posValue = root["position"];
   Serializer::check(posValue, "x", "GeometryNode");
   Serializer::check(posValue, "y", "GeometryNode");
   Serializer::check(posValue, "z", "GeometryNode");
   float xPos = posValue["x"].asFloat();
   float yPos = posValue["y"].asFloat();
   float zPos = posValue["z"].asFloat();
   glm::vec3 position(xPos, yPos, zPos);

   // Orientation
   Serializer::check(root, "orientation", "GeometryNode");
   Json::Value oriValue = root["orientation"];
   Serializer::check(oriValue, "w", "GeometryNode");
   Serializer::check(oriValue, "x", "GeometryNode");
   Serializer::check(oriValue, "y", "GeometryNode");
   Serializer::check(oriValue, "z", "GeometryNode");
   float wOri = oriValue["w"].asFloat();
   float xOri = oriValue["x"].asFloat();
   float yOri = oriValue["y"].asFloat();
   float zOri = oriValue["z"].asFloat();
   glm::quat orientation(wOri, xOri, yOri, zOri);

   // Position
   Serializer::check(root, "scale", "GeometryNode");
   Json::Value scaleValue = root["scale"];
   Serializer::check(scaleValue, "x", "GeometryNode");
   Serializer::check(scaleValue, "y", "GeometryNode");
   Serializer::check(scaleValue, "z", "GeometryNode");
   float xScale = scaleValue["x"].asFloat();
   float yScale = scaleValue["y"].asFloat();
   float zScale = scaleValue["z"].asFloat();
   glm::vec3 scale(xScale, yScale, zScale);

   // GeometryNode items
   Serializer::check(root, "model", "GeometryNode");
   std::string modelJsonName = root["model"].asString();
   ModelRef model = ModelSerializer::load(modelJsonName, scene);

   // Create the node
   GeometryNodeRef node = std::make_shared<GeometryNode>("TODO", name, model);

   // Set properties
   node->translateBy(position);
   node->rotateBy(orientation);
   node->scaleBy(scale);

   // Set up children
   Serializer::check(root, "children", "GeometryNode");
   Json::Value childrenValue = root["children"];
   ASSERT(childrenValue.isArray(), "children should be an array");
   for (int i = 0; i < childrenValue.size(); ++i) {
      NodeRef childNode = NodeSerializer::deserialize(childrenValue[i], scene);

      node->addChild(childNode);
      childNode->setParent(node);
   }

   return node;
}

} // namespace GeometryNodeSerializer
