#include "GeometryNode.h"
#include "FancyAssert.h"
#include "Loader.h"
#include "SceneGraph.h"

#include <assimp/Importer.hpp>      // C++ importer interface

GeometryNodeRef GeometryNode::fromFile(SceneGraph *graph, const std::string &name, const std::string &fileName, ShaderProgram *program) {
   // Load the mesh from the file
   Assimp::Importer importer;
   const aiScene* scene = Loader::loadScene(&importer, fileName);
   ASSERT(scene->mNumMeshes > 0, "No meshes in scene: %s", fileName.c_str());

   // TODO Support multiple meshes
   /*for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {

   }*/
   const aiMesh* mesh = scene->mMeshes[0];

   // Parse the faces
   const unsigned int numIndices = mesh->mNumFaces * 3;
   unsigned int *faceArray = new unsigned int[numIndices];
   unsigned int faceIndex = 0;
   for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
      const aiFace* face = &mesh->mFaces[t];

      memcpy(&faceArray[faceIndex], face->mIndices, 3 * sizeof(unsigned int));
      faceIndex += 3;
   }

   // Prepare the vertex array object
   GLuint vao;
   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);

   // Prepare the vertex buffer object
   GLuint vbo;
   glGenBuffers(1, &vbo);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh->mNumVertices, mesh->mVertices, GL_STATIC_DRAW);
   GLint aPosition = program->getAttribute("aPosition");
   glEnableVertexAttribArray(aPosition);
   glVertexAttribPointer(aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

   // Prepare the normal buffer object
   GLuint nbo;
   glGenBuffers(1, &nbo);
   glBindBuffer(GL_ARRAY_BUFFER, nbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh->mNumVertices, mesh->mNormals, GL_STATIC_DRAW);
   GLint aNormal = program->getAttribute("aNormal");
   glEnableVertexAttribArray(aNormal);
   glVertexAttribPointer(aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);

   // Prepare the index buffer object
   GLuint ibo;
   glGenBuffers(1, &ibo);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, faceArray, GL_STATIC_DRAW);

   // Unbind
   glBindVertexArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   delete[] faceArray;

   return GeometryNodeRef(new GeometryNode(graph, name, vao, numIndices));
}

GeometryNode::GeometryNode(SceneGraph *scene, const std::string &name, const GLuint vao, const unsigned int numIndices)
   : SceneNode(scene, name), vao(vao), numIndices(numIndices) {

}

void GeometryNode::draw(MatrixStack *matrixStack) {
   matrixStack->push();

   glBindVertexArray(vao);
   glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
   glBindVertexArray(0);

   for (NodeRef child : children) {
      child->draw(matrixStack);
   }

   matrixStack->pop();
}

void GeometryNode::tick(const double dt) {

}