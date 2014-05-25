#include "FancyAssert.h"
#include "FrameBuffer.h"

#include <iostream>

#ifndef NO_FBO

FrameBuffer::FrameBuffer()
: bufferObjectsGenerated(false), fbWidth(0), fbHeight(0) {
   // Create FrameBufferObject
   glGenFramebuffers(1, &fBObject);
}

FrameBuffer::~FrameBuffer() {
   //Delete resources
   if (bufferObjectsGenerated) {
      glDeleteTextures(1, &fBTexture);
      glDeleteRenderbuffers(1, &fBRender);
   }

   //Bind 0, which means render to back buffer, as a result, fb is unbound
   glBindFramebuffer(GL_FRAMEBUFFER, 0);
   glDeleteFramebuffers(1, &fBObject);
}

void FrameBuffer::setupToTexture2D() {
   // Determine the texture size from the viewport
   GLint viewport[4];
   glGetIntegerv(GL_VIEWPORT, viewport);
   setupToTexture2D(viewport[2], viewport[3]);
}

void FrameBuffer::setupToTexture2D(int textureWidth, int textureHeight) {
   fbWidth = textureWidth;
   fbHeight = textureHeight;

   // Get and save the texture size so that we know how big it is when we apply it as a texture.
   glBindFramebuffer(GL_FRAMEBUFFER, fBObject);

   if (bufferObjectsGenerated) {
      glDeleteTextures(1, &fBTexture);
      glDeleteRenderbuffers(1, &fBRender);
   }

   // Create texture to hold color buffer
   glGenTextures(1, &fBTexture);
   glBindTexture(GL_TEXTURE_2D, fBTexture);

   // Setup the texture parameters. How big the texture image will be, etc.
   // NULL on glTexImage2D means to reserve texture memory.
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   //Set "Rendered Texture" as our color attachment 0.
   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fBTexture, 0);

   // Create Renderbuffer Object to hold depth
   glGenRenderbuffers(1, &fBRender);
   glBindRenderbuffer(GL_RENDERBUFFER, fBRender);
   glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, textureWidth, textureHeight);
   glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, fBRender);

   checkFBOStatus();

   glBindTexture(GL_TEXTURE_2D, 0);
   glBindFramebuffer(GL_FRAMEBUFFER, 0);

   bufferObjectsGenerated = true;
}

void FrameBuffer::checkFBOStatus() {
   GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
   ASSERT(status == GL_FRAMEBUFFER_COMPLETE, "Could not setup FrameBufferObject. Error #%d\n", status);
}

void FrameBuffer::applyFBO() {
   glBindFramebuffer(GL_FRAMEBUFFER, fBObject);
}

void FrameBuffer::disableFBO() {
   glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

#else

FrameBuffer::FrameBuffer()
: bufferObjectsGenerated(false) {
}

FrameBuffer::~FrameBuffer() {
}

void FrameBuffer::setupToTexture2D() {
}

void FrameBuffer::setupToTexture2D(int textureWidth, int textureHeight) {
}

void FrameBuffer::checkFBOStatus() {
}

void FrameBuffer::applyFBO() {
}

void FrameBuffer::disableFBO() {
}

#endif