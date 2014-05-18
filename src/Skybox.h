#ifndef SKYBOX_H
#define SKYBOX_H

#include "GLIncludes.h"

#include <string>

class Model;

class Skybox {
protected:
   GLuint skyboxID, ambientMapID, ambientGlobalID;
   GLint uSkybox;
   SPtr<Model> model;

public:
   Skybox(SPtr<Model> model, const std::string &path);
   virtual ~Skybox();

   void renderSkybox(RenderData &renderData);

   GLuint getSkyboxID() {
      return skyboxID;
   }

   GLuint getAmbientMapID() {
      return ambientMapID;
   }
};

#endif