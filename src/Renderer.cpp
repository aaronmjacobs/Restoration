#include "Camera.h"
#include "GLIncludes.h"
#include "Light.h"
#include "Renderer.h"
#include "Scene.h"
#include "SceneGraph.h"
#include "ShaderProgram.h"

Renderer::Renderer(int width, int height, float fov)
   : fov(fov) {
   onWindowSizeChange(width, height);
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

void Renderer::onWindowSizeChange(int width, int height) {
   // Update the projection to match the new window size.
   projectionMatrix = glm::perspective(fov, (float)width / height, 0.1f, 100.f);
}

namespace {

// Function that draws a SceneObject
void draw(SceneObject &obj) {
   obj.draw();
}

} // namespace

void Renderer::render(Scene &scene) {
   // Clear the render buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   SPtr<Camera> camera = scene.getCamera().lock();
   if (!camera) {
      return;
   }

   // Grab the view matrix
   viewMatrix = camera->getViewMatrix();

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
      glUniformMatrix4fv(uProjMatrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

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

   // Render each item in the scene
   scene.getSceneGraph()->forEach(draw);
}
