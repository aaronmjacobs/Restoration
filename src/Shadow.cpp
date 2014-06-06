#include "Shadow.h"
#include "FancyAssert.h"

Shadow::Shadow() {
   initialized = false;

}

Shadow::~Shadow(){
   if (initialized) {
      glDeleteFramebuffers(1, &sMapID);
      glDeleteTextures(1, &depthTextureID);
   }
}

void Shadow::initialize() {
   if (initialized) {
      glDeleteFramebuffers(1, &sMapID);
      glDeleteTextures(1, &depthTextureID);
   }

   // create a framebuffer object
   glGenFramebuffers(1, &sMapID);
   glBindFramebuffer(GL_FRAMEBUFFER, sMapID);
   initialized = true;

   GLint viewport[4];
   glGetIntegerv(GL_VIEWPORT, viewport);

   // Create a depth texture (16 bits). We will be sampling from this later so we make it a TEXTURE.
   // Experimenting with the size of the shadowmap.
   glGenTextures(1, &depthTextureID);
   glBindTexture(GL_TEXTURE_2D, depthTextureID);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, viewport[2], viewport[3], 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTextureID, 0);

   // Instruct openGL that we won't bind a color texture with the currently bound FBO
   glDrawBuffer(GL_NONE);
   glReadBuffer(GL_NONE);

   checkFBOStatus();
   glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Shadow::checkFBOStatus() {
   GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
   ASSERT(status == GL_FRAMEBUFFER_COMPLETE, "Could not setup FBO for Shadows. Error #%d\n", status);
}

void Shadow::applyFBO(){
   glBindFramebuffer(GL_FRAMEBUFFER, sMapID);
   glDrawBuffer(GL_NONE);
   glReadBuffer(GL_NONE);
}

void Shadow::disableFBO(){
   glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
