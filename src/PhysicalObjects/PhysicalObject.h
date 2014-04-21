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
   * Constructs a physical oject for the given scene with the given name (unique) and model.
   */
   PhysicalObject(const std::string &jsonFileName, const std::string &name, ModelRef model);

   /**
   * Does cleanup (currently nothing!).
   */
   virtual ~PhysicalObject();

   /**
   * Checks the collision between two physical objects.
   */
   virtual bool checkCollision(PhysicalObjectRef PhysObj);

   /**
   * Steps |dt| seconds through time.
   */
   virtual void tick(const float dt) = 0;

protected:
   /**
   * Bounded box parameters for interaction between each physical object.
   */
   float xMin, xMax, yMin, yMax;

   /**
   * Move the physical object in a certain direction.
   */
   virtual void move(glm::vec3 dir) = 0;
};

#endif
