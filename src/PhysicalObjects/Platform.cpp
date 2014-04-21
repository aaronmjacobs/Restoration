#include "Platform.h"

Platform::Platform(const std::string &jsonFileName, const std::string &name, ModelRef model)
   : PhysicalObject(jsonFileName, name, model) {
}

Platform::~Platform() {
}
