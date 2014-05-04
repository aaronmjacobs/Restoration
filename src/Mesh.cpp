#include "FancyAssert.h"
#include "Loader.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

const std::string Mesh::CLASS_NAME = "Mesh";

Mesh::Mesh(const std::string &fileName)
   : fileName(fileName) {
   // Load the mesh from the file
   SPtr<Loader> loader = Loader::getInstance();
   const aiScene* scene = loader->loadAssimpScene(fileName);
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

   float xMin = 0.0f, xMax = 0.0f, yMin = 0.0f, yMax = 0.0f;
   for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
      if (i == 0) {
         xMin = mesh->mVertices[i].x;
         xMax = mesh->mVertices[i].x;
         yMin = mesh->mVertices[i].y;
         yMax = mesh->mVertices[i].y;
      }
      else {
         if (mesh->mVertices[i].x < xMin) {
            xMin = mesh->mVertices[i].x;
         }
         else if (mesh->mVertices[i].x > xMax) {
            xMax = mesh->mVertices[i].x;
         }

         if (mesh->mVertices[i].y < yMin) {
            yMin = mesh->mVertices[i].y;
         }
         else if (mesh->mVertices[i].y > yMax) {
            yMax = mesh->mVertices[i].y;
         }
      }
   }

   bounds = std::make_shared<BoundingBox>(xMin, xMax, yMin, yMax);

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

   // Buffer for vertex texture coordinates
   if (mesh->HasTextureCoords(0)) {
      float *texCoords = new float[mesh->mNumVertices * 2];
      for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {
         texCoords[k * 2] = mesh->mTextureCoords[0][k].x;
         texCoords[k * 2 + 1] = mesh->mTextureCoords[0][k].y;
      }

      glGenBuffers(1, &tbo);
      glBindBuffer(GL_ARRAY_BUFFER, tbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * mesh->mNumVertices, texCoords, GL_STATIC_DRAW);
      delete[] texCoords;
   }

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

Json::Value Mesh::serialize() const {
   Json::Value root;

   // Class name
   root["@class"] = CLASS_NAME;

   root["fileName"] = fileName;

   return root;
}
