#ifndef MODEL_H
#define MODEL_H

#include "Material.h"
#include "Mesh.h"

#include <memory>

class Model;
typedef std::shared_ptr<Model> ModelRef;

class Model {
private:
   MaterialRef material;
   MeshRef mesh;
   GLuint vao;

public:
   Model(MaterialRef material, MeshRef mesh);
   ~Model();
   void draw();
};

#endif