#ifndef MESH_H
#define MESH_H

#include "GLIncludes.h"

#include <assimp/Importer.hpp> 
#include <memory>
#include <string>

class Mesh;
typedef std::shared_ptr<Mesh> MeshRef;

/**
 * Mesh built of vertices and normals.
 */
class Mesh {
private:
   /**
    * Vertex, normal, and index buffer objects.
    */
   GLuint vbo, nbo, ibo;

   /**
    * The number of vertex indices.
    */
   unsigned int numIndices;

public:
   /**
    * Constructs a mesh from the model file with the given file name, allocating
    * the required GL buffers.
    */
   Mesh(const std::string &fileName);

   /**
    * Deallocates the GL buffers.
    */
   virtual ~Mesh();

   /**
    * Gets the vertex buffer object handle.
    */
   GLuint getVBO() {
      return vbo;
   }

   /**
    * Gets the normal buffer object handle.
    */
   GLuint getNBO() {
      return nbo;
   }

   /**
    * Gets the index buffer object handle.
    */
   GLuint getIBO() {
      return ibo;
   }

   /**
    * Gets the number of vertex indices.
    */
   unsigned int getNumIndices() {
      return numIndices;
   }
};

#endif
