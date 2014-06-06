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

   bool initialized;

public:
   /**
   * Constructs a shadow framebuffer.
   */
   Shadow();

   /**
   * Deletes shadow framebuffer.
   */
   ~Shadow();

   void initialize();

   void applyFBO();

   void disableFBO();

   void checkFBOStatus();

   GLuint getTextureID(){
      return depthTextureID;
   }
};

#endif