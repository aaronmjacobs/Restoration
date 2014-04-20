#include "PhongMaterialSerializer.h"
#include "MaterialSerializer.h"
#include "Serializer.h"
#include "../engine/IOUtils.h"

#include <memory>

namespace MaterialSerializer {

MaterialRef load(const std::string &jsonFileName) {
   Json::Value root = IOUtils::readJsonFile(Material::JSON_FOLDER_PATH + jsonFileName);

   Serializer::check(root, "@class", "Material");
   std::string className = root["@class"].asString();

   // Check which material it matches
   if (className == PhongMaterial::CLASS_NAME) {
      return PhongMaterialSerializer::load(jsonFileName);
   }

   ASSERT("Invalid class name for %s: %s", jsonFileName.c_str(), className.c_str());

   return MaterialRef();
}

} // namespace MaterialSerializer
