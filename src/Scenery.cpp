#include "Scenery.h"

Scenery::Scenery(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
   : PhysicalObject(scene, model, name) {
}

Scenery::~Scenery() {
}
