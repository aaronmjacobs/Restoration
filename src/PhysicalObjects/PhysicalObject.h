#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include "../engine/GeometryNode.h"

class PhysicalObject;
typedef std::shared_ptr<PhysicalObject> PhysicalObjectRef;

/**
* A physical object in the scene that can be interacted with.
*/
class PhysicalObject : public GeometryNode {
public:
   /**
   * Checks the collision between two physical objects.
   */
   virtual bool checkCollision(PhysicalObjectRef PhysObj);

   /**
   * Steps |dt| seconds through time.
   */
   virtual void tick(const double dt);

   /**
   * Change material of model to whichever one you're using.
   */
   virtual void changeMaterial(MaterialRef material);

protected:
   /**
   * Bounded box parameters for interaction between each physical object.
   */
   float xMin, xMax, yMin, yMax;

   /**
   * Move the physical object in a certain direction.
   */
   virtual void move(glm::vec3 dir);
};

#endif
