#ifndef MESH_H
#define MESH_H

#include "GLIncludes.h"
#include "Serializable.h"

#include <string>

/**
 * Mesh built of vertices and normals.
 */
class Mesh : public Serializable {
   /**
    * Vertex, normal, and index buffer objects.
    */
   GLuint vbo, nbo, ibo;

   /**
    * The number of vertex indices.
    */
   unsigned int numIndices;

   /**
    * Name of the file the mesh data exists in.
    */
   std::string fileName;

   /**
   * Extreme values for computing bounding box
   */
   float minX, minY, maxX, maxY;

public:
   static const std::string CLASS_NAME;

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
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

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
   unsigned int getNumIndices() const {
     return numIndices;
   }

   float getMinX() {
      return minX;
   }

   float getMaxX() {
      return maxX;
   }

   float getMinY() {
      return minY;
   }

   float getMaxY() {
      return maxY;
   }
};

#endif
