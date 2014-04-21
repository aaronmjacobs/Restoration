#ifndef PLATFORM_H
#define PLATFORM_H

#include "PhysicalObject.h"

class Platform;
typedef std::shared_ptr<Platform> PlatformRef;

class Platform : public PhysicalObject {
public:
   Platform(const std::string &jsonFileName, const std::string &name, ModelRef model);
   virtual ~Platform();
};

#endif
