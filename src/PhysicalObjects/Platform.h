#ifndef PLATFORM_H
#define PLATFORM_H

#include "PhysicalObject.h"
#include "Player.h"

#include <list>

class Platform;
typedef std::shared_ptr<Platform> PlatformRef;

class Platform : public PhysicalObject {
public:
   /**
    * Name of the class (used in deserialization to determine types).
    */
   static const std::string CLASS_NAME;
   static std::list<Platform*> allPlatforms;
   Platform(Scene *scene, const std::string &jsonFileName, const std::string &name, ModelRef model);
   virtual ~Platform();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   virtual void tick(const float dt);
   virtual void move(glm::vec3 dir);

   virtual void collideWith(PhysicalObject *physObj);
   virtual void collideWith(Player *player);
   virtual void collideWith(Platform *platform);
};

#endif
