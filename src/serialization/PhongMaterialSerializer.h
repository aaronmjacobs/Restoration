#ifndef PHONG_MATERIAL_SERIALIZER_H
#define PHONG_MATERIAL_SERIALIZER_H

#include "../PhongMaterial.h"
#include "../engine/Scene.h"
#include "../engine/lib/json/json.h"

#include <string>

namespace PhongMaterialSerializer {

PhongMaterialRef load(const std::string &jsonFileName, Scene *scene);

} // namespace PhongMaterialSerializer

#endif
