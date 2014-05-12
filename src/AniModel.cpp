#include "FancyAssert.h"
#include "IOUtils.h"
#include "Material.h"
#include "Mesh.h"
#include "AniModel.h"
#include "AniMesh.h"

const std::string AniModel::CLASS_NAME = "AniModel";

AniModel::AniModel(SPtr<Material> material, SPtr<AniMesh> mesh)
: Model(material, mesh) {
   this->aniMesh = mesh;
}

AniModel::~AniModel() {
}

Json::Value AniModel::serialize() const {
   Json::Value root = Model::serialize();

   // Class name
   root["@class"] = CLASS_NAME;

   return root;
}

void AniModel::draw() {
   SPtr<ShaderProgram> shaderProgram = material->getShaderProgram();

   // Apply the material properties (and enable the shader)
   material->apply(mesh);
   aniMesh->updateAnimation();

   // Send the bones
   float *bones = aniMesh->getBones();
   GLint bonesMatrix = shaderProgram->getUniform("bonesMatrix");
   glUniformMatrix4fv(bonesMatrix, MAX_BONES, GL_FALSE, bones);
   delete[] bones;

   // Set the weights
   glBindBuffer(GL_ARRAY_BUFFER, aniMesh->getWBO());
   GLint aWeights = shaderProgram->getAttribute("weights");
   glEnableVertexAttribArray(aWeights);
   glVertexAttribPointer(aWeights, 3, GL_FLOAT, GL_FALSE, 0, 0);

   // Set the joints
   glBindBuffer(GL_ARRAY_BUFFER, aniMesh->getJBO());
   GLint aJoints = shaderProgram->getAttribute("joints");
   glEnableVertexAttribArray(aJoints);
   glVertexAttribPointer(aJoints, 3, GL_FLOAT, GL_FALSE, 0, 0);

   // Prepare the vertex buffer object
   glBindBuffer(GL_ARRAY_BUFFER, mesh->getVBO());
   GLint aPosition = shaderProgram->getAttribute("aPosition");
   glEnableVertexAttribArray(aPosition);
   glVertexAttribPointer(aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

   // Prepare the normal buffer object
   glBindBuffer(GL_ARRAY_BUFFER, mesh->getNBO());
   GLint aNormal = shaderProgram->getAttribute("aNormal");
   glEnableVertexAttribArray(aNormal);
   glVertexAttribPointer(aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);

   // Prepare the index buffer object
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIBO());

   // Draw
   glDrawElements(GL_TRIANGLES, mesh->getNumIndices(), GL_UNSIGNED_INT, 0);

   // Unbind
   glDisableVertexAttribArray(aWeights);
   glDisableVertexAttribArray(aJoints);
   glDisableVertexAttribArray(aPosition);
   glDisableVertexAttribArray(aNormal);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   shaderProgram->disable(); // TODO Make call to material?
}
