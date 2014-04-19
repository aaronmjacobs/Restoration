#ifndef CAMERA_SERIALIZER_H
#define CAMERA_SERIALIZER_H

#include "../engine/Camera.h"

#include "../engine/lib/json/json.h"
#include <string>

namespace CameraSerializer {

CameraRef load(const std::string &jsonFileName);

} // namespace CameraSerializer

#endif
