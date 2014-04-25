#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "../engine/FancyAssert.h"
#include "../engine/Serializable.h"

#include "CameraSerializer.h"
#include "LightSerializer.h"
#include "MeshSerializer.h"
#include "ModelSerializer.h"
#include "NodeSerializer.h"
#include "GeometryNodeSerializer.h"
#include "TransformNodeSerializer.h"
#include "MaterialSerializer.h"
#include "PlatformSerializer.h"
#include "PhongMaterialSerializer.h"
#include "ShaderProgramSerializer.h"
#include "ShaderSerializer.h"
#include "TextureMaterialSerializer.h"

namespace Serializer {

void save(const Serializable &serializable);

void check(const Json::Value &value, const char *key, const char *type);

} // namespace Serializer

#endif
