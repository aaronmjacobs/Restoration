#ifndef ANIMODEL_H
#define ANIMODEL_H

#include "GLIncludes.h"
#include "Model.h"
#include "Serializable.h"
#include "Types.h"

class AniMesh;

/**
 * A three dimensional model, composed of a set of vertices / normals (mesh) and
 * visual properties, along with the shader to draw it (material).
 */
class AniModel : public Model {
protected:
   /**
    * The model's mesh (vertices / normals).
    */
   SPtr<AniMesh> aniMesh;

public:
   static const std::string CLASS_NAME;

   /**
    * Constructs the model with the given material and mesh.
    */
   AniModel(SPtr<Material> material, SPtr<AniMesh> aniMesh);

   /**
    * Does cleanup.
    */
   virtual ~AniModel();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   /**
    * Draws the model.
    */
   virtual void draw();
};

#endif
