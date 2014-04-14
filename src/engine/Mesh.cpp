#include "FancyAssert.h"
#include "Loader.h"
#include "Mesh.h"

Mesh::Mesh(const std::string &fileName) {
   // Load the mesh from the file
   Assimp::Importer importer;
   const aiScene* scene = Loader::loadScene(&importer, fileName);
   ASSERT(scene->mNumMeshes > 0, "No meshes in scene: %s", fileName.c_str());

   // TODO Support multiple meshes
   /*for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {

   }*/
   const aiMesh* mesh = scene->mMeshes[0];

   // Parse the faces
   numIndices = mesh->mNumFaces * 3;
   unsigned int *faceArray = new unsigned int[numIndices];
   unsigned int faceIndex = 0;
   for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
      const aiFace* face = &mesh->mFaces[t];

      memcpy(&faceArray[faceIndex], face->mIndices, 3 * sizeof(unsigned int));
      faceIndex += 3;
   }

   // Prepare the vertex buffer object
   glGenBuffers(1, &vbo);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh->mNumVertices, mesh->mVertices, GL_STATIC_DRAW);

   // Prepare the normal buffer object
   glGenBuffers(1, &nbo);
   glBindBuffer(GL_ARRAY_BUFFER, nbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh->mNumVertices, mesh->mNormals, GL_STATIC_DRAW);

   // Prepare the index buffer object
   glGenBuffers(1, &ibo);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, faceArray, GL_STATIC_DRAW);

   // Unbind
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   delete[] faceArray;
}

Mesh::~Mesh() {
   glDeleteBuffers(1, &vbo);
   glDeleteBuffers(1, &nbo);
   glDeleteBuffers(1, &ibo);
}
