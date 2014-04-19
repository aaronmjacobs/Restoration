#include "MeshSerializer.h"
#include "../engine/IOUtils.h"

namespace MeshSerializer {

MeshRef load(const std::string &jsonFileName) {
   Json::Value root = IOUtils::readJsonFile(Mesh::JSON_FOLDER_PATH + jsonFileName);

   std::string fileName = root["fileName"].asString();

   return MeshRef(std::make_shared<Mesh>(jsonFileName, fileName));
}

} // namespace MeshSerializer
