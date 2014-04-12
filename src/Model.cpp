#include "Model.h"

#include <iostream>

Model::Model(MaterialRef material, MeshRef mesh) {
   this->material = material;
   this->mesh = mesh;

   material->getShaderProgram()->use();

   // Prepare the vertex array object
   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);

   // Prepare the vertex buffer object
   glBindBuffer(GL_ARRAY_BUFFER, mesh->getVBO());
   GLint aPosition = material->getShaderProgram()->getAttribute("aPosition");
   glEnableVertexAttribArray(aPosition);
   glVertexAttribPointer(aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

   // Prepare the normal buffer object
   glBindBuffer(GL_ARRAY_BUFFER, mesh->getNBO());
   GLint aNormal = material->getShaderProgram()->getAttribute("aNormal");
   glEnableVertexAttribArray(aNormal);
   glVertexAttribPointer(aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);

   // Prepare the index buffer object
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIBO());

   // Unbind
   glBindVertexArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   material->getShaderProgram()->disable();
}

Model::~Model() {
   glDeleteVertexArrays(1, &vao);
}

void Model::draw() {
   material->apply();

   glBindVertexArray(vao);
   glDrawElements(GL_TRIANGLES, mesh->getNumIndices(), GL_UNSIGNED_INT, 0);
   glBindVertexArray(0);
}