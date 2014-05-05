#include "Camera.h"
#include "FancyAssert.h"
#include "Light.h"
#include "Scene.h"
#include "SceneGraph.h"
#include "ShaderProgram.h"

const std::string Scene::CLASS_NAME = "Scene";
const std::string Scene::FOLDER_NAME = "scenes";

Scene::Scene(const std::string &jsonFileName)
   : Saveable(jsonFileName), collisionHandler(*this) {
}

Scene::~Scene() {
}

Json::Value Scene::serialize() const {
   Json::Value root;

   root["@class"] = CLASS_NAME;

   // Scene graph
   if (sceneGraph) {
      root["graph"] = sceneGraph->serialize();
   }

   // Camera, lights, and shader programs determined on reload

   return root;
}

SPtr<SceneGraph> Scene::getSceneGraph() {
   return sceneGraph;
}

void Scene::setSceneGraph(SPtr<SceneGraph> sceneGraph) {
   this->sceneGraph = sceneGraph;
}

WPtr<Camera> Scene::getCamera() {
   return camera;
}

void Scene::setCamera(SPtr<Camera> camera) {
   this->camera = WPtr<Camera>(camera);
}

const std::list<WPtr<Light>>& Scene::getLights() {
   return lights;
}

const std::list<WPtr<ShaderProgram>>& Scene::getShaderPrograms() {
   return shaderPrograms;
}

CollisionHandler& Scene::getCollisionHanlder() {
   return collisionHandler;
}

void Scene::tick(const float dt) {
   for (SPtr<TickListener> listener : tickListeners) {
      listener->tick(dt);
   }

   if (sceneGraph) {
      sceneGraph->tick(dt);
   }
}

void Scene::onKeyEvent(int key, int action) {
   for (SPtr<InputListener> listener : inputListeners) {
      listener->onKeyEvent(key, action);
   }
}

void Scene::onMouseButtonEvent(int button, int action) {
   for (SPtr<InputListener> listener : inputListeners) {
      listener->onMouseButtonEvent(button, action);
   }
}

void Scene::onMouseMotionEvent(double xPos, double yPos) {
   for (SPtr<InputListener> listener : inputListeners) {
      listener->onMouseMotionEvent(xPos, yPos);
   }
}

void Scene::onWindowFocusGained() {
   // Recompile all shaders (to allow for live updating).
   // TODO Only recompile where needed? Check file mod time?
   for (WPtr<ShaderProgram> wProgram : shaderPrograms) {
      SPtr<ShaderProgram> program = wProgram.lock();
      if (program) {
         program->compileShaders();
         program->link();
      }
   }
}

void Scene::addLight(SPtr<Light> light) {
   lights.push_back(WPtr<Light>(light));
}

void Scene::removeLight(SPtr<Light> light) {
   for (std::list<WPtr<Light>>::iterator itr = lights.begin();
      itr != lights.end(); ++itr) {
      SPtr<Light> sLight = itr->lock();
      if (sLight && light == sLight) {
         lights.erase(itr);
         return;
      }
   }

   ASSERT(false, "Unable to remove light");
}

void Scene::addShaderProgram(SPtr<ShaderProgram> shaderProgram) {
   shaderPrograms.push_back(WPtr<ShaderProgram>(shaderProgram));
}

void Scene::removeShaderProgram(SPtr<ShaderProgram> shaderProgram) {
   for (std::list<WPtr<ShaderProgram>>::iterator itr = shaderPrograms.begin();
      itr != shaderPrograms.end(); ++itr) {
      SPtr<ShaderProgram> sProgram = itr->lock();
      if (sProgram && shaderProgram == sProgram) {
         shaderPrograms.erase(itr);
         return;
      }
   }

   ASSERT(false, "Unable to remove shader program");
}

void Scene::addInputListener(SPtr<InputListener> listener) {
   inputListeners.push_back(listener);
}

void Scene::removeInputListener(SPtr<InputListener> listener) {
   inputListeners.remove(listener);
}

void Scene::addTickListener(SPtr<TickListener> listener) {
   tickListeners.push_back(listener);
}

void Scene::removeTickListener(SPtr<TickListener> listener) {
   tickListeners.remove(listener);
}

