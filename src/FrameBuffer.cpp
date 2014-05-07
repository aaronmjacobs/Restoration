#include "FrameBuffer.h"
#include "FancyAssert.h"

FrameBuffer::FrameBuffer(){
   // Create FrameBufferObject
   glGenFramebuffers(1, &fBObject);
   //glBindFramebuffer(GL_FRAMEBUFFER, fBObject);
}

FrameBuffer::~FrameBuffer(){
   //Delete resources
   glDeleteTextures(1, &fBTexture);
   glDeleteRenderbuffersEXT(1, &fBRender);

   //Bind 0, which means render to back buffer, as a result, fb is unbound
   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
   glDeleteFramebuffersEXT(1, &fBObject);
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
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
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
   switch (status){
      case GL_FRAMEBUFFER_COMPLETE:
         // This is the only case it shouldn't fail on.
         break;
      default:
         ASSERT(false, "Could not setup FrameBufferObject. Error #%d\n", status);
         break;
   }
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