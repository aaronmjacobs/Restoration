#include "Camera.h"
#include "CameraDeserializer.h"
#include "FancyAssert.h"
#include "FlatSceneGraph.h"
#include "FlatSceneGraphDeserializer.h"
#include "Light.h"
#include "LightDeserializer.h"
#include "Scene.h"
#include "SceneObject.h"
#include "SceneObjectDeserializer.h"
#include "Types.h"

namespace FlatSceneGraphDeserializer {

SPtr<FlatSceneGraph> deserialize(const Json::Value &root, SPtr<Scene> scene) {
   SPtr<FlatSceneGraph> graph = std::make_shared<FlatSceneGraph>();

   bool cameraLoaded = false;

   // Load each object
   Json::Value objectsVal = root["objects"];
   ASSERT(objectsVal.isArray(), "objects should be an array");
   for (int i = 0; i < objectsVal.size(); ++i) {
      Json::Value objectVal = objectsVal[i];
      std::string className = objectVal["@class"].asString();

      SPtr<SceneObject> sceneObject;
      if (className == Light::CLASS_NAME) {
         SPtr<Light> light = LightDeserializer::deserialize(objectVal, scene);
         scene->addLight(light);
         sceneObject = light;
      } else if (className == Camera::CLASS_NAME) {
         ASSERT(!cameraLoaded, "Camera already loaded for scene graph");
         cameraLoaded = true;

         SPtr<Camera> camera = CameraDeserializer::deserialize(objectVal, scene);
         scene->setCamera(camera);
         sceneObject = camera;
      } else {
         sceneObject = SceneObjectDeserializer::deserialize(objectVal, scene);
      }

      graph->add(sceneObject);
   }

   ASSERT(cameraLoaded, "No camera loaded for scene graph");

   return graph;
}

} // namespace FlatSceneGraphDeserializer
