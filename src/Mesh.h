#ifndef MESH_H
#define MESH_H

#include "BoundingBox.h"
#include "GLIncludes.h"
#include "Serializable.h"
#include "Types.h"

#include <string>

/**
 * Mesh built of vertices and normals.
 */
class Mesh : public Serializable {
   /**
    * Vertex, normal, index, and texture buffer objects.
    */
   GLuint vbo, nbo, ibo, tbo;

   /**
    * If the mesh has a texture buffer object.
    */
   bool hasTextureBufferObject;

   /**
    * The number of vertex indices.
    */
   unsigned int numIndices;

   /**
    * Name of the file the mesh data exists in.
    */
   std::string fileName;

protected:
   /**
    * Bounding box
    */
   SPtr<BoundingBox> bounds;

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

   virtual void updateAnimation() {
   }

   virtual void hardApplyAnimation(const std::string &aniName) {
   }

   virtual void softApplyAnimation(const std::string &aniName) {
   }

   /**
    * Gets the vertex buffer object handle.
    */
   GLuint getVBO() const {
     return vbo;
   }

   /**
    * Gets the normal buffer object handle.
    */
   GLuint getNBO() const {
     return nbo;
   }

   /**
    * Gets the index buffer object handle.
    */
   GLuint getIBO() const {
     return ibo;
   }

   /**
    * Gets the texture buffer object handle.
    */
   GLuint getTBO() const;

   /**
    * Gets the number of vertex indices.
    */
   unsigned int getNumIndices() const {
     return numIndices;
   }

   SPtr<BoundingBox> getBounds() {
      return bounds;
   }
};

#endif
