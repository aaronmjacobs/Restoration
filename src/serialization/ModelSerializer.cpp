#include "ModelSerializer.h"
#include "Serializer.h"
#include "../engine/IOUtils.h"

#include <memory>

namespace ModelSerializer {

ModelRef load(const std::string &jsonFileName, Scene *scene) {
   Json::Value root = IOUtils::readJsonFile(Model::JSON_FOLDER_PATH + jsonFileName);

   // Load the material
   Serializer::check(root, "material", "Model");
   std::string materialJsonFileName = root["material"].asString();
   // TODO Make reusable
   MaterialRef material = MaterialSerializer::load(materialJsonFileName, scene);

   // Load the mesh
   Serializer::check(root, "mesh", "Model");
   std::string meshJsonFileName = root["mesh"].asString();
   // TODO Make reusable
   MeshRef mesh = MeshSerializer::load(meshJsonFileName);

   return std::make_shared<Model>(jsonFileName, material, mesh);
}

} // namespace ModelSerializer
