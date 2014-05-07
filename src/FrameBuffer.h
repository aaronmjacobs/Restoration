#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "GLIncludes.h"

class FrameBuffer{
public:
   /* Create the Frame Buffer Object to be used in a scene.  *
    * MUST call a setup function from FrameBuffer to setup   *
    * fBTexture and fBRender for the scene.                  */
   FrameBuffer();

   /* Render to Texture for a 2D texture with depth testing */
   void setupToTexture2D(int textureWidth, int textureHeight);

   /* Delete the FrameBuffer and all of its associated things */
   virtual ~FrameBuffer();

   /* Check the status of the FrameBuffer */
   void checkFBOStatus();

   /* Apply the FBO to the scene */
   void applyFBO();

   /* Return the texture id of the FrameBuffer */
   GLuint getTextureID() const {
      return fBTexture;
   }

protected:
   /* Create object to capture frame */
   GLuint fBObject;

   /* Create object for texturing */
   GLuint fBTexture;
   
   /* create object for depth testing */
   GLuint fBRender;

   /* width and height of the texture */
   int textureWidth, textureHeight;

private:


};

#endif