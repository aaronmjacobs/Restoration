#ifndef SKYBOX_H
#define SKYBOX_H

#include "GLIncludes.h"

#include <string>

class Mesh;
class ShaderProgram;

class Skybox {
public:

   Skybox(SPtr<ShaderProgram> shaderProgram, SPtr<Mesh> mesh, const std::string &xpos, const std::string &xneg, const std::string &ypos,
      const std::string &yneg, const std::string &zpos, const std::string &zneg, const std::string &skydir);

   void renderSkybox();

   void releaseSkybox();

protected:
   GLuint skybox_id;
   GLint uSkybox, aSkyboxCoord;

   /**
   * Shader program with which to draw.
   */
   SPtr<ShaderProgram> shaderProgram;

   /**
   * The mesh with which to draw.
   */
   SPtr<Mesh> mesh;


private:

};

#endif