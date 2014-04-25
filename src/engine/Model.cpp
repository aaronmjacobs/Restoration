#include "FancyAssert.h"
#include "Model.h"

const std::string Model::CLASS_NAME = "Model";
const std::string Model::JSON_FOLDER_PATH = "data/model/";

Model::Model(const std::string &jsonFileName, MaterialRef material, MeshRef mesh)
   : Serializable(jsonFileName) {
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

   root["material"] = material->getJsonFileName();
   root["mesh"] = mesh->getJsonFileName();

   return root;
}

void Model::draw() {
   // Apply the material properties (and enable the shader)
   material->apply(mesh);

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

   // Draw
   glDrawElements(GL_TRIANGLES, mesh->getNumIndices(), GL_UNSIGNED_INT, 0);

   // Unbind
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   material->disable();
   material->getShaderProgram()->disable(); // TODO Make call to material?
}
