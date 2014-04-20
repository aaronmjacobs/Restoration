#ifndef LIGHT_SERIALIZER_H
#define LIGHT_SERIALIZER_H

#include "../engine/lib/json/json.h"
#include "../engine/Light.h"

#include <string>

namespace LightSerializer {

LightRef load(const std::string &jsonFileName);

} // namespace LightSerializer

#endif
