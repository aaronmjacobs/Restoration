#include "FancyAssert.h"
#include "lib/stb_image.h"
#include "Material.h"
#include "Mesh.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Skybox.h"

struct ImgInfo {
   int w;
   int h;
   int comp;
   unsigned char *pixels;
};

Skybox::Skybox(SPtr<Model> model, const std::string &name)
: model(model) {
   const std::string &path = "data/textures/skyboxes/";

   // Grab the required uniform from the skybox model's shader
   SPtr<ShaderProgram> shaderProgram = model->getMaterial()->getShaderProgram();
   uSkybox = shaderProgram->getUniform("uSkybox");

   // Load the skybox
   loadCubemap(path + name + "/", &skyboxID);

   // Load the ambient map
   loadCubemap(path + name + "/ambient/", &ambientMapID);
}

void Skybox::loadCubemap(const std::string &path, GLuint *id) {
   const std::string &rightName = "right.png";
   const std::string &leftName = "left.png";
   const std::string &upName = "up.png";
   const std::string &downName = "down.png";
   const std::string &backName = "back.png";
   const std::string &frontName = "front.png";

   // Generate the cubemap
   glGenTextures(1, id);
   glBindTexture(GL_TEXTURE_CUBE_MAP, *id);

   // Load the images
   ImgInfo right = loadImage(path + rightName);
   ImgInfo left = loadImage(path + leftName);
   ImgInfo up = loadImage(path + upName);
   ImgInfo down = loadImage(path + downName);
   ImgInfo back = loadImage(path + backName);
   ImgInfo front = loadImage(path + frontName);

   // Set up handling for the texture cubemap for when too near/too far away from image.
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

   // Send the image data to the GPU
   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, right.w, right.h, 0, GL_RGB, GL_UNSIGNED_BYTE, right.pixels);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, left.w, left.h, 0, GL_RGB, GL_UNSIGNED_BYTE, left.pixels);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, up.w, up.h, 0, GL_RGB, GL_UNSIGNED_BYTE, up.pixels);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, down.w, down.h, 0, GL_RGB, GL_UNSIGNED_BYTE, down.pixels);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, back.w, back.h, 0, GL_RGB, GL_UNSIGNED_BYTE, back.pixels);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, front.w, front.h, 0, GL_RGB, GL_UNSIGNED_BYTE, front.pixels);

   // Free the image data
   stbi_image_free(right.pixels);
   stbi_image_free(left.pixels);
   stbi_image_free(up.pixels);
   stbi_image_free(down.pixels);
   stbi_image_free(back.pixels);
   stbi_image_free(front.pixels);

   glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

ImgInfo Skybox::loadImage(const std::string &fileName) {
   ImgInfo image;

   FILE *file = fopen(fileName.c_str(), "rb");
   ASSERT(file, "Unable to load image: %s", fileName.c_str());
   image.pixels = stbi_load_from_file(file, &image.w, &image.h, &image.comp, 0);
   ASSERT(image.comp == 3, "Invalid image composition value: %d", image.comp);
   fclose(file);

   return image;
}

void Skybox::renderSkybox() {
   // Enable the skybox shader program
   model->getMaterial()->getShaderProgram()->use();

   glDisable(GL_DEPTH_TEST);
   glEnable(GL_TEXTURE_CUBE_MAP);
   glActiveTexture(GL_TEXTURE0 + skyboxID);
   glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxID);
   glUniform1i(uSkybox, skyboxID);

   model->draw();

   glDisable(GL_TEXTURE_CUBE_MAP);
   glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
   glEnable(GL_DEPTH_TEST);
}
