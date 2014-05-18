#include "FancyAssert.h"
#include "lib/stb_image.h"
#include "Loader.h"
#include "Material.h"
#include "Mesh.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Skybox.h"

const std::string Skybox::CLASS_NAME = "Skybox";

struct ImgInfo {
   int w;
   int h;
   int comp;
   unsigned char *pixels;
};

Skybox::Skybox(SPtr<Model> model, const std::string &name)
: model(model), name(name) {
   const std::string &path = "data/textures/skyboxes/";

   // Grab the required uniform from the skybox model's shader
   SPtr<ShaderProgram> shaderProgram = model->getMaterial()->getShaderProgram();
   uSkybox = shaderProgram->getUniform("uSkybox");

   Loader& loader = Loader::getInstance();

   // Load the skybox
   skyboxID = loader.loadCubemap(path + name + "/");

   // Load the ambient map
   ambientMapID = loader.loadCubemap(path + name + "/ambient/");

   // Load the ambient global color
   ambientGlobalID = loader.loadTexture(path + name + "/ambient/global.png");
}

Skybox::~Skybox() {
   glDeleteTextures(1, &skyboxID);
   glDeleteTextures(1, &ambientMapID);
   glDeleteTextures(1, &ambientGlobalID);
}

Json::Value Skybox::serialize() const {
   Json::Value root;

   root["@class"] = CLASS_NAME;

   root["name"] = name;

   root["model"] = model->serialize();

   return root;
}

void Skybox::renderSkybox(RenderData &renderData) {
   // Enable the skybox shader program
   model->getMaterial()->getShaderProgram()->use();

   glDisable(GL_DEPTH_TEST);
   glEnable(GL_TEXTURE_CUBE_MAP);
   glActiveTexture(GL_TEXTURE0 + skyboxID);
   glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxID);
   glUniform1i(uSkybox, skyboxID);

   model->draw(renderData);

   glDisable(GL_TEXTURE_CUBE_MAP);
   glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
   glEnable(GL_DEPTH_TEST);

   // Set the ambient map and global ambient color
   renderData.set("ambientMapID", ambientMapID);
   renderData.set("ambientGlobalID", ambientGlobalID);
}
