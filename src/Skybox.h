#ifndef SKYBOX_H
#define SKYBOX_H

#include "GLIncludes.h"

#include <string>

class Model;
struct ImgInfo;

class Skybox {
protected:
   GLuint skyboxID, ambientMapID;
   GLint uSkybox;
   SPtr<Model> model;

   void loadCubemap(const std::string &path, GLuint *id);
   ImgInfo loadImage(const std::string &fileName);

public:
   Skybox(SPtr<Model> model, const std::string &path);

   void renderSkybox(RenderData &renderData);

   GLuint getSkyboxID() {
      return skyboxID;
   }

   GLuint getAmbientMapID() {
      return ambientMapID;
   }
};

#endif