#include "Camera.h"
#include "FrameBuffer.h"
#include "GLIncludes.h"
#include "Light.h"
#include "Renderer.h"
#include "RenderState.h"
#include "Scene.h"
#include "SceneGraph.h"
#include "ShaderProgram.h"

Renderer::Renderer() {
}

Renderer::~Renderer() {
}

void Renderer::prepare() {
   // Set the clear (background) color.
   glClearColor(0.0, 0.0, 0.0, 0.0);

   // Depth Buffer Setup
   glClearDepth(1.0f);
   glDepthFunc(GL_LEQUAL);
   glEnable(GL_DEPTH_TEST);

   // Back face culling
   glCullFace(GL_BACK);
}

namespace {

// Function that draws a SceneObject
void drawStencil(SceneObject &obj) {
   obj.draw(STENCIL_STATE);
}

void drawLight(SceneObject &obj) {
   obj.draw(LIGHTWORLD_STATE);
}

void drawDark(SceneObject &obj) {
   obj.draw(DARKWORLD_STATE);
}

} // namespace

void Renderer::setupStencil(){
   glEnable(GL_STENCIL_TEST);
   // disable color and depth buffers
   glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
   glDepthMask(GL_FALSE);

   glStencilFunc(GL_NEVER, 1, 0xFF); // never pass stencil test
   glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);  // replace stencil buffer values to ref=1
   glStencilMask(0xFF); // stencil buffer free to write
   glClear(GL_STENCIL_BUFFER_BIT);  // first clear stencil buffer by writing default stencil value (0) to all of stencil buffer.
   //now draw stencil shape at stencil shape pixel locations in stencil buffer replace stencil buffer values to ref = 1
}

void Renderer::render(Scene &scene) {
   // Clear the render buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   SPtr<Camera> camera = scene.getCamera().lock();
   if (!camera) {
      return;
   }

   // Grab the view matrix
   glm::mat4 viewMatrix = camera->getViewMatrix();

   // Set up the matrices and lights
   const unsigned int numLights = scene.getLights().size();
   glm::vec3 cameraPos = camera->getPosition();
   unsigned int lightIndex;
   for (WPtr<ShaderProgram> wShaderProgram : scene.getShaderPrograms()) {
      SPtr<ShaderProgram> shaderProgram = wShaderProgram.lock();
      if (!shaderProgram) {
         continue;
      }

      shaderProgram->use();

      // Projection matrix
      GLint uProjMatrix = shaderProgram->getUniform("uProjMatrix");
      glUniformMatrix4fv(uProjMatrix, 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));

      // View matrix
      GLint uViewMatrix = shaderProgram->getUniform("uViewMatrix");
      glUniformMatrix4fv(uViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

      // Number of lights
      GLuint uNumLights = shaderProgram->getUniform("uNumLights");
      glUniform1i(uNumLights, numLights);

      // Camera position
      GLint uCameraPos = shaderProgram->getUniform("uCameraPos");
      glUniform3fv(uCameraPos, 1, glm::value_ptr(cameraPos));

      // Lights
      lightIndex = 0;
      for (WPtr<Light> wLight : scene.getLights()) {
         SPtr<Light> light = wLight.lock();
         if (!light) {
            continue;
         }

         light->draw(*shaderProgram, lightIndex);
         ++lightIndex;
      }
   }
   // Render each item in the scene (to stencil buffer)
   setupStencil();
   scene.getSceneGraph()->forEach(drawStencil);
   // enable color and depth buffers.
   glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
   glDepthMask(GL_TRUE);

   // no more modifying of stencil buffer on stencil and depth pass.
   glStencilMask(0x00);
   // can also be achieved by glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

   // stencil test: only pass stencil test at stencilValue == 1 (Assuming depth test would pass.) 
   // and write actual content to depth and color buffer only at stencil shape locations.
   glStencilFunc(GL_EQUAL, 1, 0xFF);

   // Render each item in the scene (to frame buffer object)
   scene.getSceneGraph()->forEach(drawLight);

   // Render each item in the scene (to actual window)
   //scene.getSceneGraph()->forEach(drawDark);
}
