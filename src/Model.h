#ifndef MODEL_H
#define MODEL_H

#include "GLIncludes.h"
#include "Serializable.h"
#include "Types.h"

class Material;
class Mesh;
class RenderData;

/**
 * A three dimensional model, composed of a set of vertices / normals (mesh) and
 * visual properties, along with the shader to draw it (material).
 */
class Model : public Serializable {
protected:
   /**
    * The model's material (visual properties + shader).
    */
   SPtr<Material> material;

   /**
    * The model's mesh (vertices / normals).
    */
   SPtr<Mesh> mesh;

public:
   static const std::string CLASS_NAME;

   /**
    * Constructs the model with the given material and mesh.
    */
   Model(SPtr<Material> material, SPtr<Mesh> mesh);

   /**
    * Does cleanup.
    */
   virtual ~Model();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   /**
    * Draws the model.
    */
   virtual void draw(const RenderData &renderData);

   /**
    * Gets the model's material.
    */
   SPtr<Material> getMaterial();

   /**
    * Gets the model's mesh.
    */
   SPtr<Mesh> getMesh();

   /**
    * Sets the model's material.
    */
   void setMaterial(SPtr<Material> material) {
      this->material = material;
   }
};

#endif
