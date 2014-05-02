#include "FancyAssert.h"
#include "FlatSceneGraph.h"
#include "FlatSceneGraphDeserializer.h"
#include "Scene.h"
#include "SceneGraph.h"
#include "SceneGraphDeserializer.h"
#include "Types.h"

namespace SceneGraphDeserializer {

SPtr<SceneGraph> deserialize(const Json::Value &root, SPtr<Scene> scene) {
   std::string className = root["@class"].asString();

   if (className == FlatSceneGraph::CLASS_NAME) {
      return FlatSceneGraphDeserializer::deserialize(root, scene);
   }

   ASSERT(false, "Invalid class name for SceneGraph: %s", className.c_str());   

   return SPtr<SceneGraph>();
}

} // namespace SceneGraphDeserializer
