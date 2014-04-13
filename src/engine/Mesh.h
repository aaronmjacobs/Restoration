#ifndef MESH_H
#define MESH_H

#include "GLIncludes.h"

#include <assimp/Importer.hpp> 

#include <memory>
#include <string>

class Mesh;
typedef std::shared_ptr<Mesh> MeshRef;

class Mesh {
private:
   GLuint vbo, nbo, ibo;
   unsigned int numIndices;

public:
   Mesh(const std::string &fileName);
   ~Mesh();
   GLuint getVBO() {
      return vbo;
   }
   GLuint getNBO() {
      return nbo;
   }
   GLuint getIBO() {
      return ibo;
   }
   unsigned int getNumIndices() {
      return numIndices;
   }
};

#endif