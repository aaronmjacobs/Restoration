#ifndef MATERIAL_SERIALIZER_H
#define MATERIAL_SERIALIZER_H

#include "../engine/Material.h"
#include "../engine/lib/json/json.h"

#include <string>

namespace MaterialSerializer {

MaterialRef load(const std::string &jsonFileName);

} // namespace MaterialSerializer

#endif
