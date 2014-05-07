#include "FancyAssert.h"
#include "lib/stb_image.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Skybox.h"

struct skyImgInfo{
   int w;
   int h;
   int comp;
   unsigned char *pixels;
};

<<<<<<< HEAD
Skybox::Skybox(SPtr<ShaderProgram> shaderProgram, SPtr<Mesh> mesh, const std::string xpos, const std::string xneg, const std::string ypos, const std::string yneg,
   const std::string zpos, const std::string zneg, const std::string skydir)
=======
Skybox::Skybox(SPtr<ShaderProgram> shaderProgram, SPtr<Mesh> mesh, const std::string &xpos, const std::string &xneg, const std::string &ypos, const std::string &yneg,
   const std::string &zpos, const std::string &zneg, const std::string &skydir)
>>>>>>> 768e00b4b80780e2205f420839347b9e8abc12a7
   :shaderProgram(shaderProgram), mesh(mesh) {
   
   uSkybox = shaderProgram->getUniform("uSkybox");
   aSkyboxCoord = shaderProgram->getAttribute("aSkyboxCoord");

   FILE *file;
   struct skyImgInfo xp, xn, yp, yn, zp, zn;

   //Generate 6 skybox ids to reference the images that will be loaded.
   //glGenTextures(SKYBOX_NUM_TEXTURES, &(skybox_id));

   glGenTextures(1, &(skybox_id));
   glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_id);


   file = fopen((skydir + xpos).c_str(), "rb");
   ASSERT(file, "Null skybox file %s", (skydir + xpos).c_str());
   xp.pixels = stbi_load_from_file(file, &(xp.w), &(xp.h), &(xp.comp), 0);
   fclose(file);

   file = fopen((skydir + xneg).c_str(), "rb");
   ASSERT(file, "Null skybox file %s", (skydir + xneg).c_str());
   xn.pixels = stbi_load_from_file(file, &(xn.w), &(xn.h), &(xn.comp), 0);
   fclose(file);

   file = fopen((skydir + ypos).c_str(), "rb");
   ASSERT(file, "Null skybox file %s", (skydir + xpos).c_str());
   yp.pixels = stbi_load_from_file(file, &(yp.w), &(yp.h), &(yp.comp), 0);
   fclose(file);

   file = fopen((skydir + yneg).c_str(), "rb");
   ASSERT(file, "Null skybox file %s", (skydir + xpos).c_str());
   yn.pixels = stbi_load_from_file(file, &(yn.w), &(yn.h), &(yn.comp), 0);
   fclose(file);

   file = fopen((skydir + zpos).c_str(), "rb");
   ASSERT(file, "Null skybox file %s", (skydir + xpos).c_str());
   zp.pixels = stbi_load_from_file(file, &(zp.w), &(zp.h), &(zp.comp), 0);
   fclose(file);

   file = fopen((skydir + zneg).c_str(), "rb");
   ASSERT(file, "Null skybox file %s", (skydir + xpos).c_str());
   zn.pixels = stbi_load_from_file(file, &(zn.w), &(zn.h), &(zn.comp), 0);
   fclose(file);

   // Set up handling for the texture cubemap for when too near/too far away from image. 
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

   if (xp.comp == 3 && xn.comp == 3 && yp.comp == 3 && yn.comp == 3 && zp.comp == 3 && zn.comp == 3){
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, xp.w, xp.h, 0, GL_RGB, GL_UNSIGNED_BYTE, xp.pixels);
      glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, xn.w, xn.h, 0, GL_RGB, GL_UNSIGNED_BYTE, xn.pixels);
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, yp.w, yp.h, 0, GL_RGB, GL_UNSIGNED_BYTE, yp.pixels);
      glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, yn.w, yn.h, 0, GL_RGB, GL_UNSIGNED_BYTE, yn.pixels);
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, zp.w, zp.h, 0, GL_RGB, GL_UNSIGNED_BYTE, zp.pixels);
      glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, zn.w, zn.h, 0, GL_RGB, GL_UNSIGNED_BYTE, zn.pixels);
   }
   
   // Free all of the raw pointers for no memory leaks.
   stbi_image_free(xp.pixels);
   stbi_image_free(xn.pixels);
   stbi_image_free(yp.pixels);
   stbi_image_free(xp.pixels);
   stbi_image_free(zp.pixels);
   stbi_image_free(zn.pixels);
    
   glBindTexture(GL_TEXTURE_2D, 0);
}

void Skybox::renderSkybox()
{
   glDisable(GL_DEPTH_TEST);
   // glDisable(GL_LIGHTING); Deprecated enum - should just be handled now by shader

   shaderProgram->use();

   glEnable(GL_TEXTURE_CUBE_MAP);
   glActiveTexture(GL_TEXTURE1);
   glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_id);

   glUniform1i(uSkybox, skybox_id);
   glEnableVertexAttribArray(aSkyboxCoord);
   glBindBuffer(GL_ARRAY_BUFFER, mesh->getTBO());
   glVertexAttribPointer(aSkyboxCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

}

void Skybox::releaseSkybox()
{
   glDisable(GL_TEXTURE_CUBE_MAP);
   /* Create once working. */
}