#ifndef GEOMETRY_DESERIALIZER_H
#define GEOMETRY_DESERIALIZER_H

#include "Types.h"

class Geometry;

namespace GeometryDeserializer {

SPtr<Geometry> deserialize(const Json::Value &root, SPtr<Scene> const scene);

} // namespace GeometryDeserializer

#endif
