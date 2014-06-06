#include "Shadow.h"
#include "FancyAssert.h"

Shadow::Shadow(){
   // create a framebuffer object
   glGenFramebuffers(1, &sMapID);
   glBindFramebuffer(GL_FRAMEBUFFER, sMapID);

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

Shadow::~Shadow(){
   glDeleteFramebuffers(1, &sMapID);
   glDeleteTextures(1, &depthTextureID);
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

void Shadow::setLightMatrix(glm::vec3 lightInvDir, SPtr<ShaderProgram> program)
{
   // Moving from unit cube [-1,1] to [0,1]  
   const glm::mat4 bias = {
      0.5, 0.0, 0.0, 0.0,
      0.0, 0.5, 0.0, 0.0,
      0.0, 0.0, 0.5, 0.0,
      0.5, 0.5, 0.5, 1.0 };

   // Depth Bias MVP matrix
   uDepthMVP = program->getUniform("uDepthMVP");

   // Compute the MVP matrix from the light's point of view
   glm::mat4 depthProjectionMatrix = glm::ortho<float>(-30, -15, 0, 15, 0, 100);
   glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(-100, 0, 0), glm::vec3(0, 1, 0));

   dBiasMVP = bias * depthProjectionMatrix * depthViewMatrix;
   glUniformMatrix4fv(uDepthMVP, 1, GL_FALSE, glm::value_ptr(dBiasMVP));
}