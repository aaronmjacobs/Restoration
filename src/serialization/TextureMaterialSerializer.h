#ifndef TEXTURE_MATERIAL_SERIALIZER_H
#define TEXTURE_MATERIAL_SERIALIZER_H

#include "../TextureMaterial.h"
#include "../engine/Scene.h"
#include "../engine/lib/json/json.h"

#include <string>

namespace TextureMaterialSerializer {

   TextureMaterialRef load(const std::string &jsonFileName, Scene *scene);

} // namespace TextureMaterialSerializer

#endif
