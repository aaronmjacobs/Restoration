#ifndef PHONG_MATERIAL_DESERIALIZER_H
#define PHONG_MATERIAL_DESERIALIZER_H

#include "Types.h"

class PhongMaterial;
class Scene;

namespace PhongMaterialDeserializer {

SPtr<PhongMaterial> deserialize(const std::string &fileName, SPtr<Scene> scene);

} // namespace PhongMaterialDeserializer

#endif
