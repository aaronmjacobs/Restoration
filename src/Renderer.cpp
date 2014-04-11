#include "Renderer.h"
#include "SceneGraph.h"

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::render(SceneGraph *scene) {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // TODO Camera shit

   // TODO Light shit

   for (NodeRef node : scene->getChildren()) {
      node->draw(&matrixStack);
   }
}