#ifndef MODEL_H
#define MODEL_H

#include "Material.h"
#include "Mesh.h"

#include <memory>

class Model;
typedef std::shared_ptr<Model> ModelRef;

/**
 * A three dimensional model, composed of a set of vertices / normals (mesh) and
 * visual properties, along with the shader to draw it (material).
 */
class Model {
private:
   /**
    * The model's material (visual properties + shader).
    */
   MaterialRef material;

   /**
    * The model's mesh (vertices / normals).
    */
   MeshRef mesh;

   /**
    * Vertex array object to simplify the drawing process.
    */
   GLuint vao;

public:
   /**
    * Constructs the model with the given material and mesh.
    */
   Model(MaterialRef material, MeshRef mesh);

   /**
    * Does cleanup.
    */
   virtual ~Model();

   /**
    * Draws the model.
    */
   virtual void draw();

   /**
    * Gets the model's material.
    */
   MaterialRef getMaterial() {
      return material;
   }
};

#endif
