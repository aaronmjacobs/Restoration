#ifndef MODEL_H
#define MODEL_H

#include "Material.h"
#include "Mesh.h"
#include "Serializable.h"

#include <memory>

class Model;
typedef std::shared_ptr<Model> ModelRef;

/**
 * A three dimensional model, composed of a set of vertices / normals (mesh) and
 * visual properties, along with the shader to draw it (material).
 */
class Model : public Serializable {
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
    * Name of the class (used in deserialization to determine types).
    */
   static const std::string CLASS_NAME;

   /**
    * Path to the folder that serialized (JSON) files will be stored in.
    */
   static const std::string JSON_FOLDER_PATH;

   /**
    * Constructs the model with the given material and mesh.
    */
   Model(const std::string &jsonFileName, MaterialRef material, MeshRef mesh);

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
   virtual void draw();

   /**
    * Gets the model's material.
    */
   MaterialRef getMaterial() {
      return material;
   }

   virtual std::string getJsonFolderName() const {
      return JSON_FOLDER_PATH;
   }
};

#endif
