#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include "../engine/GeometryNode.h"

#include <list>

class Platform;
class Player;
class PhysicalObject;
typedef std::shared_ptr<PhysicalObject> PhysicalObjectRef;

typedef struct {
   float xMin, xMax, yMin, yMax;
} AxisAlignedBoundingBox;

/**
* A physical object in the scene that can be interacted with.
*/
class PhysicalObject : public GeometryNode {
public:
   // TODO Make a non-global list in the scene
   static std::list<PhysicalObject*> physicalObjects;

   /**
   * Constructs a physical oject for the given scene with the given name (unique) and model.
   */
   PhysicalObject(Scene *scene, const std::string &jsonFileName, const std::string &name, ModelRef model);

   /**
   * Does cleanup (currently nothing!).
   */
   virtual ~PhysicalObject();

   /**
   * Checks the collision between two physical objects.
   */
   virtual bool checkCollision(PhysicalObject *physObj);

   /**
   * Steps |dt| seconds through time.
   */
   virtual void tick(const float dt) = 0;

   void setBounds(AxisAlignedBoundingBox bounds) {
      this->boundingBox = bounds;
   }

   AxisAlignedBoundingBox getBounds();

   virtual void collideWith(PhysicalObject *physObj) = 0;
   virtual void collideWith(Player *player) = 0;
   virtual void collideWith(Platform *platform) = 0;

protected:
   /**
   * Bounded box parameters for interaction between each physical object.
   */
   AxisAlignedBoundingBox boundingBox;

   /**
   * Move the physical object in a certain direction.
   */
   virtual void move(glm::vec3 dir) = 0;
};

#endif
