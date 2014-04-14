#include "Renderer.h"
#include "SceneGraph.h"

Renderer::Renderer(int width, int height, float fov) {
   this->fov = fov;
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
}

void Renderer::onWindowSizeChange(int width, int height) {
   // Update the projection to match the new window size.
   projectionMatrix = glm::perspective(fov, (float)width / height, 0.1f, 100.f);
}

void Renderer::onWindowFocusGained() {
   // Recompile all shaders (to allow for live updating).
   // TODO Only recompile where needed? Check file mod time?
   for (ShaderProgramRef program : shaderPrograms) {
      program->compileShaders();
      program->link();
   }
}

void Renderer::addLight(LightRef light) {
   lights.push_back(light);
}

void Renderer::addShaderProgram(ShaderProgramRef shaderProgram) {
   shaderPrograms.push_back(shaderProgram);
}

void Renderer::render(SceneGraph *scene) {
   // Clear the render buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Set up view matrix
   viewMatrix = scene->getCamera()->getViewMatrix();

   // Set up lights for each shader
   const unsigned int numLights = lights.size();
   glm::vec3 cameraPos = scene->getCamera()->getPosition();
   unsigned int lightIndex;
   for (ShaderProgramRef shaderProgram : shaderPrograms) {
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
      for (LightRef light : lights) {
         light->draw(shaderProgram, lightIndex);
         ++lightIndex;
      }
   }

   // Render each item in the scene
   for (NodeRef node : scene->getChildren()) {
      node->draw(&modelMatrixStack);
   }
}
