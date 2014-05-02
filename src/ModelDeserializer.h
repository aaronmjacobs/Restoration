#ifndef MODEL_DESERIALIZER_H
#define MODEL_DESERIALIZER_H

#include "Types.h"

class Model;
class Scene;

namespace ModelDeserializer {

SPtr<Model> deserialize(const Json::Value &root, SPtr<Scene> scene);

} // namespace ModelDeserializer

#endif
