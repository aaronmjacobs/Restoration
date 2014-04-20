#ifndef MODEL_SERIALIZER_H
#define MODEL_SERIALIZER_H

#include "../engine/Model.h"
#include "../engine/Scene.h"
#include "../engine/lib/json/json.h"

#include <string>

namespace ModelSerializer {

ModelRef load(const std::string &jsonFileName, Scene *scene);

} // namespace ModelSerializer

#endif
