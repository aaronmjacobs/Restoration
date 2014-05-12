#ifndef SKYBOX_H
#define SKYBOX_H

#include "GLIncludes.h"

#include <string>

class Model;

class Skybox {
protected:
   GLuint skybox_id;
   GLint uSkybox, aSkyboxCoord;

   SPtr<Model> model;

public:
   Skybox(SPtr<Model> model, const std::string &xpos, const std::string &xneg, const std::string &ypos,
      const std::string &yneg, const std::string &zpos, const std::string &zneg, const std::string &skydir);

   void renderSkybox();

   void releaseSkybox();
};

#endif