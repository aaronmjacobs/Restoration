#include "FancyAssert.h"
#include "IOUtils.h"
#include "Scene.h"
#include "SceneGraph.h"
#include "SceneGraphDeserializer.h"
#include "Types.h"

namespace SceneDeserializer {

SPtr<Scene> deserialize(const std::string &fileName) {
   Json::Value root = IOUtils::readJsonFile(IOUtils::getPath<Scene>(fileName));

   SPtr<Scene> scene = std::make_shared<Scene>(fileName);

   // Loads the scene graph, including the camera, any lights, and any shader program
   SPtr<SceneGraph> graph = SceneGraphDeserializer::deserialize(root["graph"], scene);
   scene->setSceneGraph(graph);

   return scene;
}

} // namespace SceneDeserializer
