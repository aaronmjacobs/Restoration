#include "SceneGraph.h"
#include "FancyAssert.h"

SceneGraph::SceneGraph()
   : rootNode(this, "root") {
}

SceneGraph::~SceneGraph() {

}

void SceneGraph::draw() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //glUniformMatrix4fv(uViewMatrix, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));

   rootNode.draw();
}

void SceneGraph::tick() {
   rootNode.tick();
}