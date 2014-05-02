#ifndef MATERIAL_DESERIALIZER_H
#define MATERIAL_DESERIALIZER_H

#include "Types.h"

class Material;
class Scene;

namespace MaterialDeserializer {

SPtr<Material> deserialize(const std::string &fileName, SPtr<Scene> scene);

} // namespace MaterialDeserializer

#endif
