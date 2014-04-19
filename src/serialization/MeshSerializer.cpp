#include "MeshSerializer.h"
#include "../engine/IOUtils.h"

namespace MeshSerializer {

Json::Value serialize(const Mesh &mesh) {
   Json::Value root;
   root["fileName"] = mesh.getFileName();
   return root;
}

MeshRef deserialize(const Json::Value &root) {
   std::string fileName = root["fileName"].asString();

   return MeshRef(std::make_shared<Mesh>(fileName));
}

void save(const Mesh &mesh, const std::string &fileName) {
   IOUtils::writeJsonFile(serialize(mesh), fileName);
}

MeshRef load(const std::string &fileName) {
   return deserialize(IOUtils::readJsonFile(fileName));
}

} // namespace MeshSerializer
