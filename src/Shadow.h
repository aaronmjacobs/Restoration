#ifndef SHADOW_H
#define SHADOW_H

#include "Types.h"
#include "ShaderProgram.h"
#include "FrameBuffer.h"
#include "GLIncludes.h"
#include "GLMIncludes.h"


class Shadow {
protected:
   /* Framebuffer that holds the shadowmap ID */
   GLuint sMapID;

   /* Depth texture ID*/
   GLuint depthTextureID;

   /* Depth Bias MVP glint for light */
   GLint uDepthMVP;

   /* Depth bias mvp for light */
   glm::mat4 dBiasMVP;

public:
   /**
   * Constructs a shadow framebuffer.
   */
   Shadow();

   /**
   * Deletes shadow framebuffer.
   */
   ~Shadow();

   void setLightMatrix(glm::vec3 lightInvDir, SPtr<ShaderProgram> program);

   void applyFBO();

   void disableFBO();

   void checkFBOStatus();

   GLuint getTextureID(){
      return depthTextureID;
   }

   GLint getDepthMVPID(){
      return uDepthMVP;
   }

   glm::mat4 getDepthMVPMatrix(){
      return dBiasMVP;
   }
};

#endif