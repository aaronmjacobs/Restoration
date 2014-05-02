#ifndef CAMERA_DESERIALIZER_H
#define CAMERA_DESERIALIZER_H

#include "Types.h"

class Camera;

namespace CameraDeserializer {

SPtr<Camera> deserialize(const Json::Value &root, SPtr<Scene> const scene);

} // namespace CameraDeserializer

#endif
