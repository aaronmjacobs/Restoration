#ifndef PLATFORM_SERIALIZER_H
#define PLATFORM_SERIALIZER_H

#include "../PhysicalObjects/Platform.h"
#include "../engine/Scene.h"
#include "../engine/lib/json/json.h"

#include <string>

namespace PlatformSerializer {

PlatformRef load(const std::string &jsonFileName, Scene *scene);

PlatformRef deserialize(const Json::Value &root, Scene *scene);

} // namespace PlatformSerializer

#endif
