#include "Renderer.h"
#include "SceneGraph.h"

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::addLight(LightRef light) {
   lights.push_back(light);
}

void Renderer::addShaderProgram(ShaderProgramRef shaderProgram) {
   shaderPrograms.push_back(shaderProgram);
}

void Renderer::render(SceneGraph *scene) {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Set up view matrix
   viewMatrix = scene->getCamera()->getViewMatrix();

   // Set up lights for each shader
   const unsigned int numLights = lights.size();
   unsigned int lightIndex;
   for (ShaderProgramRef shaderProgram : shaderPrograms) {
      shaderProgram->use();
      GLuint uNumLights = shaderProgram->getUniform("uNumLights");
      glUniform1i(uNumLights, numLights);

      lightIndex = 0;
      for (LightRef light : lights) {
         light->draw(shaderProgram, lightIndex);
         ++lightIndex;
      }
   }

   for (NodeRef node : scene->getChildren()) {
      node->draw(&modelMatrixStack);
   }
}