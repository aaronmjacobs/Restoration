#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "../engine/FancyAssert.h"
#include "../engine/Serializable.h"

#include "CameraSerializer.h"
#include "MeshSerializer.h"

namespace Serializer {

void save(const Serializable &serializable, const std::string &fileName);

void check(const Json::Value &value, const char *key, const char *type);

} // namespace Serializer

#endif
