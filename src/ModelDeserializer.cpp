#include "FancyAssert.h"
#include "MaterialDeserializer.h"
#include "MeshDeserializer.h"
#include "Model.h"
#include "ModelDeserializer.h"
#include "Scene.h"
#include "Types.h"

class Material;
class Mesh;

namespace ModelDeserializer {

SPtr<Model> deserialize(const Json::Value &root, SPtr<Scene> scene) {
   SPtr<Material> material = MaterialDeserializer::deserialize(root["material"].asString(), scene);
   SPtr<Mesh> mesh = MeshDeserializer::deserialize(root["mesh"]);

   return std::make_shared<Model>(material, mesh);
}

} // namespace ModelDeserializer
