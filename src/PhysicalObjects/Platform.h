#ifndef PLATFORM_H
#define PLATFORM_H

#include "PhysicalObject.h"
#include "Player.h"

#include <list>

class Platform;
typedef std::shared_ptr<Platform> PlatformRef;

class Platform : public PhysicalObject {
public:
   static std::list<Platform*> allPlatforms;
   Platform(Scene *scene, const std::string &jsonFileName, const std::string &name, ModelRef model);
   virtual ~Platform();
   void collideWith(Player *player);
};

#endif
