#include "Camera.h"
#include "CatmulRomCameraController.h"
#include "FancyAssert.h"
#include "FirstPersonCameraController.h"
#include "FollowCameraController.h"
#include "LifeParticle.h"
#include "Light.h"
#include "Player.h"
#include "Scene.h"
#include "SceneGraph.h"
#include "ShaderProgram.h"
#include "Skybox.h"

const std::string Scene::CLASS_NAME = "Scene";
const std::string Scene::FOLDER_NAME = "scenes";

Scene::Scene(const std::string &jsonFileName)
   : Saveable(jsonFileName), collisionHandler(*this), editMode(false) {
   playerDeathTime = 0.0f;
   lastCheckpointPos = glm::vec3(0.0f);
      numPlayerDeaths = 0;
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

   // Skyboxes
   root["lightSkybox"] = lightSkybox->serialize();
   root["darkSkybox"] = darkSkybox->serialize();

   // Ground plane
   root["groundPlane"] = groundPlaneInfo;

   // Camera, lights, and shader programs determined on reload

   return root;
}

void Scene::postLoad() {
   // Create the camera controllers
   SPtr<Player> player = getPlayer().lock();
   followCameraController = std::make_shared<FollowCameraController>(getCamera().lock(), player, 10.0f, -0.2f, -1.45f);
   fpCameraController = std::make_shared<FirstPersonCameraController>(getCamera().lock());

   glm::vec3 finalPos(0.0f), finalLookAt(0.0f);
   if (player) {
      finalPos = player->getPosition() + glm::vec3(0.0f, 1.0f, 10.0f);
      finalLookAt = player->getPosition() + glm::vec3(0.0f, 1.0f, 0.0f); // TODO Canted angle?
   }
   std::vector<glm::vec3> cameraPoints, lookAtPoints;

   // Camera points

   cameraPoints.push_back(glm::vec3(190.0f, 0.0f, 0.0f));
   cameraPoints.push_back(glm::vec3(150.0f, 10.0f, 0.0f));
   cameraPoints.push_back(glm::vec3(0.0f, 2.0f, 10.0f));
   cameraPoints.push_back(glm::vec3(0.0f, 2.0f, 0.0f));
   cameraPoints.push_back(glm::vec3(-50.0f, 20.0f, 5.0f));
   cameraPoints.push_back(finalPos);

   // Look at points
   lookAtPoints.push_back(glm::vec3(100.0f, 2.0f, 0.0f));
   lookAtPoints.push_back(glm::vec3(0.0f, 2.0f, 0.0f));
   lookAtPoints.push_back(glm::vec3(-10.0f, 2.0f, 0.0f));
   lookAtPoints.push_back(glm::vec3(-20.0f, 20.0f, 0.0f));
   lookAtPoints.push_back(glm::vec3(-40.0f, 0.0f, 0.0f));
   lookAtPoints.push_back(finalLookAt);

   cinematicCameraController = std::make_shared<CatmulRomCameraController>(getCamera().lock(), 30.0f, cameraPoints, lookAtPoints);

   std::vector<glm::vec3> storyCameraPoints, storyLookAtPoints;

   // Camera points
   storyCameraPoints.push_back(glm::vec3(900.0f, 15.5f, 5.25f));
   storyCameraPoints.push_back(glm::vec3(900.0f, -15.5f, 5.25f));

   // Look at points
   storyLookAtPoints.push_back(glm::vec3(900.0f, 15.5f, 0.0f));
   storyLookAtPoints.push_back(glm::vec3(900.0f, -15.5f, 0.0f));

   storyIntroCameraController = std::make_shared<CatmulRomCameraController>(getCamera().lock(), 90.0f, storyCameraPoints, storyLookAtPoints);

   setCameraController(storyIntroCameraController);

   if (player) {
      lastCheckpointPos = player->getPosition();
   }
}

void Scene::setEditMode(bool editMode) {
   this->editMode = editMode;
   sceneGraph->staticObjectsModified();

   if (editMode) {
      setCameraController(fpCameraController);
   } else {
      setCameraController(followCameraController);
   }
}

void Scene::onWin() {
   std::vector<glm::vec3> cameraPoints, lookAtPoints;

   // Camera points
   glm::vec3 playerPos = player->getPosition();
   cameraPoints.push_back(playerPos + glm::vec3(0.0f, 1.0f, 10.0f));
   cameraPoints.push_back(playerPos + glm::vec3(10.0f, 1.0f, 0.0f));
   cameraPoints.push_back(playerPos + glm::vec3(0.0f, 1.0f, -10.0f));
   cameraPoints.push_back(playerPos + glm::vec3(-10.0f, 1.0f, 0.0f));
   cameraPoints.push_back(playerPos + glm::vec3(0.0f, 1.0f, 10.0f));
   cameraPoints.push_back(playerPos + glm::vec3(0.0f, 1.0f, 10.0f));
   cameraPoints.push_back(playerPos + glm::vec3(0.0f, 10.0f, 10.0f));
   cameraPoints.push_back(playerPos + glm::vec3(0.0f, 50.0f, 10.0f));

   // Look at points
   lookAtPoints.push_back(playerPos);
   lookAtPoints.push_back(playerPos);
   lookAtPoints.push_back(playerPos);
   lookAtPoints.push_back(playerPos);
   lookAtPoints.push_back(playerPos);
   lookAtPoints.push_back(playerPos);
   lookAtPoints.push_back(playerPos + glm::vec3(0.0f, 30.0f, 0.0f));
   lookAtPoints.push_back(playerPos + glm::vec3(0.0f, 500.0f, 0.0f));

   cinematicCameraController = std::make_shared<CatmulRomCameraController>(getCamera().lock(), 10.0f, cameraPoints, lookAtPoints);
   setCameraController(cinematicCameraController);

   player->resetInputState();

   LifeParticle::createEffect(player->getScene().lock(),
                              player->getPosition() + glm::vec3(0.0f, 5.0f, 0.0f),                // Position
                              glm::vec3(0.0f, 20.0f, 0.0f),              // Velocity
                              5.0f,                                  // Size
                              500.0f,   // Number of particles
                              15.0f,                                 // Duration (seconds)
                              5.0f,        // Particle spread
                              500.0f,       // Total health amount
                              true);        // Force health
}

SPtr<Skybox> Scene::getLightSkybox() {
   return lightSkybox;
}

void Scene::setLightSkybox(SPtr<Skybox> lightSkybox) {
   this->lightSkybox = lightSkybox;
}

SPtr<Skybox> Scene::getDarkSkybox() {
   return darkSkybox;
}

void Scene::setDarkSkybox(SPtr<Skybox> darkSkybox) {
   this->darkSkybox = darkSkybox;
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

WPtr<Player> Scene::getPlayer() {
   if (!player || !player->isAlive()) {
      return WPtr<Player>();
   }

   return player;
}

void Scene::setPlayer(SPtr<Player> player) {
   this->player = player;
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

void Scene::setAudio(SPtr<Audio> audio) {
   this->audio = audio;
}

SPtr<Audio> Scene::getAudio() {
   return audio;
}

void Scene::tick(const float dt) {
   if (!player->isAlive()) {
      playerDeathTime += dt;

      if (playerDeathTime > DEATH_TIME) {
         numPlayerDeaths++;
         playerDeathTime = 0.0f;
         player->unmarkForRemoval();
         player->setHealth(Player::BASE_HEALTH);
         player->setPosition(lastCheckpointPos);
         player->setVelocity(glm::vec3(0.0f));

         sceneGraph->addPhys(player);
         SPtr<Scene> scene = player->getScene().lock();
         if (scene) {
            LifeParticle::createEffect(scene,
                                       lastCheckpointPos + glm::vec3(0.0f, 10.0f, 0.0f),                // Position
                                       glm::vec3(0.0f),              // Velocity
                                       5.0f,                                  // Size
                                       100,   // Number of particles
                                       15.0f,                                 // Duration (seconds)
                                       5.0f,        // Particle spread
                                       numPlayerDeaths * 5.0f);       // Total health amount
         }

      }
   }

   // Camera control
   if (cameraController) {
      cameraController->tick(dt);
   }

   if (cameraController == storyIntroCameraController && storyIntroCameraController->doneAnimating()) {
      setCameraController(cinematicCameraController);
   } else if (cameraController == cinematicCameraController && cinematicCameraController->doneAnimating()) {
      setCameraController(followCameraController);
   }

   for (SPtr<TickListener> listener : tickListeners) {
      listener->tick(dt);
   }

   if (sceneGraph && !isInEditMode()) {
      sceneGraph->tick(dt);
   }
}

void Scene::setCheckpoint(glm::vec3 checkpoint) {
   if (checkpoint.x > lastCheckpointPos.x) {
      lastCheckpointPos = checkpoint;
      Particle::createEffect(player->getScene().lock(),
                             lastCheckpointPos,  // Position
                             glm::vec3(0.0f),         // Velocity
                             false,                   // Gravity enabled
                             5.0f,                    // Size
                             50,                      // Number of particles
                             4.0f,                    // Duration (seconds)
                             25.0f,                   // Particle spread
                             true);                   // Stencil mode
   }
}

void Scene::setCameraController(SPtr<CameraController> cam) {
   cameraController = cam;
   cameraController->reset();
}

void Scene::onKeyEvent(int key, int action) {
   if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
      if (cameraController == storyIntroCameraController) {
         setCameraController(cinematicCameraController);
      } else if (cameraController == cinematicCameraController) {
         setCameraController(followCameraController);
      }
   }

   SPtr<Player> sPlayer = player;
   if (sPlayer && cameraController == followCameraController) {
      sPlayer->onKeyEvent(key, action);
   }

   if (cameraController) {
      cameraController->onKeyEvent(key, action);
   }

   for (SPtr<InputListener> listener : inputListeners) {
      listener->onKeyEvent(key, action);
   }
}

void Scene::onMouseButtonEvent(int button, int action) {
   SPtr<Player> sPlayer = player;
   if (sPlayer && cameraController == followCameraController) {
      sPlayer->onMouseButtonEvent(button, action);
   }

   if (cameraController) {
      cameraController->onMouseButtonEvent(button, action);
   }

   for (SPtr<InputListener> listener : inputListeners) {
      listener->onMouseButtonEvent(button, action);
   }
}

void Scene::onMouseMotionEvent(double xPos, double yPos) {
   SPtr<Player> sPlayer = player;
   if (sPlayer && cameraController == followCameraController) {
      sPlayer->onMouseMotionEvent(xPos, yPos);
   }

   if (cameraController) {
      cameraController->onMouseMotionEvent(xPos, yPos);
   }

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

