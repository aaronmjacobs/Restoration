#include "Scene.h"

Scene::Scene(SceneGraphRef sceneGraph, CameraRef camera)
   : sceneGraph(sceneGraph), camera(camera) {
}

Scene::~Scene() {
}

void Scene::tick(const float dt) {
   for (TickListener *listener : tickListeners) {
      listener->tick(dt);
   }

   sceneGraph->tick(dt);
}

void Scene::onKeyEvent(int key, int action) {
   for (InputListener *listener : inputListeners) {
      listener->onKeyEvent(key, action);
   }
}

void Scene::onMouseButtonEvent(int button, int action) {
   for (InputListener *listener : inputListeners) {
      listener->onMouseButtonEvent(button, action);
   }
}

void Scene::onMouseMotionEvent(double xPos, double yPos) {
   for (InputListener *listener : inputListeners) {
      listener->onMouseMotionEvent(xPos, yPos);
   }
}

void Scene::onWindowFocusGained() {
   // Recompile all shaders (to allow for live updating).
   // TODO Only recompile where needed? Check file mod time?
   for (ShaderProgramRef program : shaderPrograms) {
      program->compileShaders();
      program->link();
   }
}

void Scene::addLight(LightRef light) {
   lights.push_back(light);
}

void Scene::removeLight(LightRef light) {
   lights.remove(light);
}

void Scene::addShaderProgram(ShaderProgramRef shaderProgram) {
   shaderPrograms.push_back(shaderProgram);
}

void Scene::removeShaderProgram(ShaderProgramRef shaderProgram) {
   shaderPrograms.remove(shaderProgram);
}

void Scene::addInputListener(InputListener *listener) {
   inputListeners.push_back(listener);
}

void Scene::removeInputListener(InputListener *listener) {
   inputListeners.remove(listener);
}

void Scene::addTickListener(TickListener *listener) {
   tickListeners.push_back(listener);
}

void Scene::removeTickListener(TickListener *listener) {
   tickListeners.remove(listener);
}
