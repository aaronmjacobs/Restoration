#ifndef SCENERY_H
#define SCENERY_H

#include "PhysicalObject.h"

class Scenery : public PhysicalObject {
public:
   Scenery(SPtr<Scene> scene, SPtr<Model> model, const std::string &name = "");
   virtual ~Scenery();
};

#endif
