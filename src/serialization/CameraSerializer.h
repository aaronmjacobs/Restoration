#ifndef CAMERA_SERIALIZER_H
#define CAMERA_SERIALIZER_H

#include "../engine/Camera.h"

#include <jsoncpp/json.h>
#include <string>

namespace CameraSerializer {

CameraRef deserialize(const Json::Value &root);

CameraRef load(const std::string &fileName);

} // namespace CameraSerializer

#endif
