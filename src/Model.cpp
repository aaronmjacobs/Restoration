#include "FancyAssert.h"
#include "IOUtils.h"
#include "Material.h"
#include "Mesh.h"
#include "Model.h"
#include "RenderData.h"

const std::string Model::CLASS_NAME = "Model";

Model::Model(SPtr<Material> material, SPtr<Mesh> mesh) {
   ASSERT(material, "Null material");
   ASSERT(mesh, "Null mesh");
   this->material = material;
   this->mesh = mesh;
}

Model::~Model() {
}

Json::Value Model::serialize() const {
   Json::Value root;

   // Class name
   root["@class"] = CLASS_NAME;

   // Material
   root["material"] = material->getJsonFileName();

   // Mesh
   root["mesh"] = mesh->serialize();

   return root;
}

void Model::draw(const RenderData &renderData) {
   // Apply the material properties (and enable the shader)
   material->apply(renderData, *mesh);
   SPtr<ShaderProgram> shaderProgram = material->getShaderProgram();

   // Prepare the vertex buffer object
   glBindBuffer(GL_ARRAY_BUFFER, mesh->getVBO());
   GLint aPosition = shaderProgram->getAttribute("aPosition");
   glEnableVertexAttribArray(aPosition);
   glVertexAttribPointer(aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

   // Prepare the normal buffer object
   GLint aNormal = 0;
   bool hasNormals = shaderProgram->hasAttribute("aNormal");
   if (hasNormals) {
      glBindBuffer(GL_ARRAY_BUFFER, mesh->getNBO());
      aNormal = shaderProgram->getAttribute("aNormal");
      glEnableVertexAttribArray(aNormal);
      glVertexAttribPointer(aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
   }

   // Prepare the index buffer object
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIBO());

   // Draw
   glDrawElements(GL_TRIANGLES, mesh->getNumIndices(), GL_UNSIGNED_INT, 0);

   // Unbind
   glDisableVertexAttribArray(aPosition);
   if (hasNormals) {
      glDisableVertexAttribArray(aNormal);
   }
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   material->disable();
}

SPtr<Material> Model::getMaterial() {
   return material;
}

SPtr<Mesh> Model::getMesh() {
   return mesh;
}
