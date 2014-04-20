#ifndef MATERIAL_SERIALIZER_H
#define MATERIAL_SERIALIZER_H

#include "../engine/Material.h"
#include "../engine/Scene.h"
#include "../engine/lib/json/json.h"

#include <string>

namespace MaterialSerializer {

MaterialRef load(const std::string &jsonFileName, Scene *scene);

} // namespace MaterialSerializer

#endif
