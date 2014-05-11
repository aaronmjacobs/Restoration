// Fancy assertions
#include "FancyAssert.h"

// OpenGL / GLFW
#include "GLIncludes.h"

// GLM
#include "GLMIncludes.h"

#include "audio/Audio.h"
#include "FlatSceneGraph.h"
#include "Loader.h"
#include "Renderer.h"
#include "Scene.h"
#include "SceneGraph.h"
#include "SceneObject.h"
#include "Types.h"

// ***************************** Temporary

#include "Light.h"
#include "Mesh.h"
#include "Material.h"
#include "Model.h"
#include "Geometry.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "PhongMaterial.h"
#include "Camera.h"
#include "FirstPersonCameraController.h"
#include "IOUtils.h"
#include "LevelEditor.h"

#include "MovableObject.h"
#include "PhysicalObject.h"
#include "Scenery.h"

// ***************************** Temporary

// STL
#include <cerrno>
#include <iostream>
#include <fstream>
#include <string>

namespace {

const int WIDTH = 1280, HEIGHT = 720;
const float FOV = glm::radians(80.0f);

SPtr<Audio> audio;
SPtr<Scene> scene;
Renderer renderer;
SPtr<Light> light;
SPtr<LevelEditor> levelEdit;

void errorCallback(int error, const char* description) {
   ASSERT(false, "Error %d: %s", error, description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
   if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
      glfwSetWindowShouldClose(window, GL_TRUE);
   }

   scene->onKeyEvent(key, action);
}

void mouseClickCallback(GLFWwindow *window, int button, int action, int mods) {
   scene->onMouseButtonEvent(button, action);
}

void mouseMotionCallback(GLFWwindow *window, double xPos, double yPos) {
   scene->onMouseMotionEvent(xPos, yPos);
}

void focusCallback(GLFWwindow* window, GLint focused) {
   if (focused) {
      scene->onWindowFocusGained();
   }
}

void windowSizeCallback(GLFWwindow* window, int width, int height) {
   SPtr<Camera> camera = scene->getCamera().lock();
   if (camera) {
      camera->onWindowSizeChange(width, height);
   }
}

void load() {
   SPtr<Loader> loader = Loader::getInstance();
   scene = loader->loadScene("testScene");
   levelEdit = std::make_shared<LevelEditor>(scene);

   SPtr<FirstPersonCameraController> cameraController = std::make_shared<FirstPersonCameraController>(scene->getCamera().lock());
   scene->addTickListener(cameraController);
   scene->addInputListener(cameraController);
   scene->addInputListener(levelEdit);
}

/*void test() {
   SPtr<SceneGraph> graph = scene->getSceneGraph();

   SPtr<Mesh> mesh = std::make_shared<Mesh>("data/meshes/cello_and_stand.obj");
   SPtr<Loader> loader = Loader::getInstance();
   SPtr<Material> material2 = loader->loadMaterial(scene, "otherMaterial");
   //IOUtils::save(*material2, "testMaterial2");

   SPtr<Model> model = std::make_shared<Model>(material2, mesh);

   SPtr<Scenery> scenery = std::make_shared<Scenery>(scene, model, "derp");
   scenery->translateBy(glm::vec3(-3.0f, 0.0f, 0.0f));
   scenery->rotateBy(glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

   graph->add(scenery);

   SPtr<FirstPersonCameraController> cameraController = std::make_shared<FirstPersonCameraController>(scene->getCamera().lock());
   scene->addTickListener(cameraController);
   scene->addInputListener(cameraController);

   light = std::make_shared<Light>(scene, glm::vec3(0.3f), 0.1f, 0.005f, 0.001f);
   light->setPosition(glm::vec3(-5.0f, 0.0f, 0.0f));
   scene->addLight(light);
   graph->add(light);

   //IOUtils::save(*scene, "testScene2");
}*/

/*void physTest() {
   SPtr<SceneGraph> graph = scene->getSceneGraph();

   SPtr<Mesh> mesh = std::make_shared<Mesh>("data/meshes/cello_and_stand.obj");
   SPtr<Loader> loader = Loader::getInstance();
   SPtr<Material> material = loader->loadMaterial(scene, "otherMaterial");

   SPtr<Model> model = std::make_shared<Model>(material, mesh);

   SPtr<MovableObject> physOne = std::make_shared<MovableObject>(scene, model, "one");
   SPtr<MovableObject> physTwo = std::make_shared<MovableObject>(scene, model, "two");

   physOne->setPosition(glm::vec3(0.0f, 10.0f, 0.0f));
   physOne->setAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

   graph->addPhys(physOne);
   graph->addPhys(physTwo);
}*/

} // namespace

int main(int argc, char *argv[]) {
   // Initialize GLFW
   GLFWwindow* window;
   glfwSetErrorCallback(errorCallback);
   ASSERT(glfwInit(), "Unable to init glfw");

/*#ifdef __APPLE__
   // Set hints to use OpenGL 3.3
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif*/

   // Enable anti-aliasing
   glfwWindowHint(GLFW_SAMPLES, 4);

   // Create the window
   window = glfwCreateWindow(WIDTH, HEIGHT, "Restoration", NULL, NULL);
   ASSERT(window, "Unable to create GLFW window");

   // Set the OpenGL context, and window callbacks
   glfwMakeContextCurrent(window);
   glfwSetWindowSizeCallback(window, windowSizeCallback);
   glfwSetWindowFocusCallback(window, focusCallback);
   glfwSetKeyCallback(window, keyCallback);
   glfwSetMouseButtonCallback(window, mouseClickCallback);
   glfwSetCursorPosCallback(window, mouseMotionCallback);

#ifdef _WIN32
   // Initialize GLEW
   ASSERT(glewInit() == GLEW_OK, "Unable to init glew");
#endif

   // Enable vsync
   glfwSwapInterval(1);

   double start = glfwGetTime();

   audio = std::make_shared<Audio>();
   audio->systemInit();
   audio->loadSound("Restoration_5_4.ogg", true);
   audio->loadSound("win.wav", false);

   // Load the scene
   load();
   scene->setAudio(audio);

   //physTest();
   
   // Send initial window size callback (to let camera build perspecitve matrix)
   windowSizeCallback(NULL, WIDTH, HEIGHT);

   std::cout << "Loading time: " << (glfwGetTime() - start) << std::endl;

   // Prepare for rendering (sets up OpenGL stuff)
   renderer.prepare();

   // Timing values
   double lastTime = glfwGetTime();
   double accumulator = 0.0;
   const double dt = 1.0 / 60.0;

   // Game loop
   while (!glfwWindowShouldClose(window)) {
      // Calculate the frame time
      double now = glfwGetTime();
      double frameTime = glm::min(now - lastTime, 0.25); // Cap the frame time to .25 seconds to prevent spiraling
      lastTime = now;

      // Update the scene
      accumulator += frameTime;
      while (accumulator >= dt) {
         scene->tick(dt);
		 levelEdit->tick(dt);
         accumulator -= dt;
      }

      // Render the scene
      renderer.render(*scene);

      // Display the rendered scene
      glfwSwapBuffers(window);

      // Poll for events
      glfwPollEvents();
   }

   scene.reset();

   audio->cleanUp();

   // Clean up GLFW
   glfwDestroyWindow(window);
   glfwTerminate();

   // Done!
   exit(EXIT_SUCCESS);
}