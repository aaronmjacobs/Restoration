#include "FancyAssert.h"
#include "IOUtils.h"
#include "Material.h"
#include "MaterialDeserializer.h"
#include "PhongMaterial.h"
#include "PhongMaterialDeserializer.h"
#include "Scene.h"
#include "Types.h"

namespace MaterialDeserializer {

SPtr<Material> deserialize(const std::string &fileName, SPtr<Scene> scene) {
   Json::Value root = IOUtils::readJsonFile(IOUtils::getPath<Material>(fileName));
   std::string className = root["@class"].asString();

   if (className == PhongMaterial::CLASS_NAME) {
      return PhongMaterialDeserializer::deserialize(fileName, scene);
   }
   
   ASSERT(false, "Invalid class name for Material: %s", className.c_str());

   return SPtr<Material>();
}

} // namespace MaterialDeserializer
