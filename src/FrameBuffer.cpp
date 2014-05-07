#include "FancyAssert.h"
#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(){
   // Create FrameBufferObject
   glGenFramebuffers(1, &fBObject);
   //glBindFramebuffer(GL_FRAMEBUFFER, fBObject);
}

FrameBuffer::~FrameBuffer(){
   //Delete resources
   glDeleteTextures(1, &fBTexture);
   glDeleteRenderbuffers(1, &fBRender);

   //Bind 0, which means render to back buffer, as a result, fb is unbound
   glBindFramebuffer(GL_FRAMEBUFFER, 0);
   glDeleteFramebuffers(1, &fBObject);
}

void FrameBuffer::setupToTexture2D(int textureWidth, int textureHeight){
   this->textureWidth = textureWidth;
   this->textureHeight = textureHeight;

   // Create texture to hold color buffer
   glGenTextures(1, &fBTexture);
   glBindTexture(GL_TEXTURE_2D, fBTexture);

   // Setup the texture parameters. How big the texture image will be, etc.
   // NULL on glTexImage2D means to reserve texture memory. 
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   //Set "Rendered Texture" as our color attachment 0.
   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fBTexture, 0);

   // Create Renderbuffer Object to hold depth
   glGenRenderbuffers(1, &fBRender);
   glBindRenderbuffer(GL_RENDERBUFFER, fBRender);
   glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, textureWidth, textureWidth);
   glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fBRender);

   checkFBOStatus();
}

void FrameBuffer::checkFBOStatus(){
   GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
   ASSERT(status == GL_FRAMEBUFFER_COMPLETE, "Could not setup FrameBufferObject. Error #%d\n", status);
}

void FrameBuffer::applyFBO(){
   glBindFramebuffer(GL_FRAMEBUFFER, fBObject);
   glViewport(0, 0, (GLsizei)textureWidth, (GLsizei)textureHeight);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClearColor(.0f, .0f, .0f, 1.0f);

   //set up the texture unit
   glEnable(GL_TEXTURE_2D);
   glActiveTexture(GL_TEXTURE1);
   glBindTexture(GL_TEXTURE_2D, fBTexture);
}