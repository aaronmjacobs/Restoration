#include "Scene.h"
#include "SceneObject.h"

const std::string SceneObject::CLASS_NAME = "SceneObject";

SceneObject::SceneObject(SPtr<Scene> const scene, const std::string &name) :
   scene(WPtr<Scene>(scene)), name(name), markedForRemoval(false) {
   scale = glm::vec3(1.0f);
}

SceneObject::~SceneObject() {
}

Json::Value SceneObject::serialize() const {
   Json::Value root;

   root["@class"] = CLASS_NAME;

   root["name"] = name;

   // Position
   Json::Value posValue;
   posValue["x"] = position.x;
   posValue["y"] = position.y;
   posValue["z"] = position.z;
   root["position"] = posValue;

   // Orientation
   Json::Value oriValue;
   oriValue["w"] = orientation.w;
   oriValue["x"] = orientation.x;
   oriValue["y"] = orientation.y;
   oriValue["z"] = orientation.z;
   root["orientation"] = oriValue;

   // Scale
   Json::Value scaleValue;
   scaleValue["x"] = scale.x;
   scaleValue["y"] = scale.y;
   scaleValue["z"] = scale.z;
   root["scale"] = scaleValue;

   return root;
}

glm::vec3 SceneObject::getPosition() {
   return position;
}

glm::quat SceneObject::getOrientation() {
   return orientation;
}

glm::vec3 SceneObject::getScale() {
   return scale;
}

void SceneObject::setPosition(const glm::vec3 &position) {
   this->position = position;
}

void SceneObject::setOrientation(const glm::quat &orientation) {
   this->orientation = orientation;
}

void SceneObject::setScale(const glm::vec3 &scale) {
   this->scale = scale;
}

void SceneObject::translateBy(const glm::vec3 &trans) {
   position += trans;
}

void SceneObject::rotateBy(const glm::quat &rot) {
   orientation *= rot;
}

void SceneObject::scaleBy(const glm::vec3 &sc) {
   scale *= sc;
}

bool SceneObject::shouldBeRemoved() {
   return markedForRemoval;
}

void SceneObject::markForRemoval() {
   markedForRemoval = true;
}