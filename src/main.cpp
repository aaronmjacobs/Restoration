#include "audio/Audio.h"
#include "Camera.h"
#include "FancyAssert.h"
#include "GLIncludes.h"
#include "GLMIncludes.h"
#include "LifeParticle.h"
#include "IOUtils.h"
#include "LevelEditor.h"
#include "Loader.h"
#include "Player.h"
#include "Renderer.h"
#include "Scene.h"
#include "TextureUnitManager.h"
#include "Types.h"

#include <iostream>
#include <string>

namespace {

const int WIDTH = 1280, HEIGHT = 720;
const float FOV = glm::radians(80.0f);

GLFWwindow* window;
SPtr<Audio> audio;
SPtr<Scene> scene;
Renderer renderer;
SPtr<LevelEditor> levelEdit;

void loadLevel(const std::string &name);

void errorCallback(int error, const char* description) {
   ASSERT(false, "Error %d: %s", error, description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
   if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
      glfwSetWindowShouldClose(window, GL_TRUE);
   }

   if (action == GLFW_PRESS && key == GLFW_KEY_L) {
      std::cout << "Which level would you like to load?: ";
      std::string levelName;
      std::cin >> levelName;
      loadLevel(levelName);
   }

   levelEdit->onKeyEvent(key, action);
   scene->onKeyEvent(key, action);
}

void mouseClickCallback(GLFWwindow *window, int button, int action, int mods) {
   levelEdit->onMouseButtonEvent(button, action);
   scene->onMouseButtonEvent(button, action);
}

void mouseMotionCallback(GLFWwindow *window, double xPos, double yPos) {
   levelEdit->onMouseMotionEvent(xPos, yPos);
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

   renderer.onWindowSizeChange(width, height);
}

void monitorCallback(GLFWmonitor *monitor, int event) {
   renderer.onMonitorChange();
}

void loadLevel(const std::string &name) {
   std::string levelPath = IOUtils::getPath<Scene>(name);
   if (!IOUtils::canRead(levelPath)) {
      std::cout << "Unable to read from file: " << levelPath << std::endl;
      return;
   }

   // Grab the current width and height of the window
   int windowWidth = WIDTH, windowHeight = HEIGHT;
   if (scene) {
      SPtr<Camera> camera = scene->getCamera().lock();
      if (camera) {
         windowWidth = camera->getWindowWidth();
         windowHeight = camera->getWindowHeight();
      }
   }

   // Clear the old level
   scene.reset();
   Loader::resetSingleton();

   // Reset the texture unit manager
   TextureUnitManager::reset();

   // Load the new level
   Loader& loader = Loader::getInstance();
   scene = loader.loadScene(name);
   scene->postLoad();

   // Attach the level editor
   levelEdit = std::make_shared<LevelEditor>(scene);

   // Attach the audio system
   scene->setAudio(audio);

   // Prepare particle effects
   Particle::initialize(scene);

   // Send initial window size callback (to let camera build perspecitve matrix)
   windowSizeCallback(NULL, windowWidth, windowHeight);

   // Send initial motion callback to get the mouse position
   double xPos, yPos;
   glfwGetCursorPos(window, &xPos, &yPos);
   mouseMotionCallback(window, xPos, yPos);
}

} // namespace

int main(int argc, char *argv[]) {
   // Initialize GLFW
   glfwSetErrorCallback(errorCallback);
   int glfwInitRes = glfwInit();
   ASSERT(glfwInitRes, "Unable to init glfw");

/*#ifdef __APPLE__
   // Set hints to use OpenGL 3.3
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif*/

   // Enable anti-aliasing
   glfwWindowHint(GLFW_SAMPLES, 2);

   // Create the window
   window = glfwCreateWindow(WIDTH, HEIGHT, "Restoration", NULL, NULL);
   ASSERT(window, "Unable to create GLFW window");

   // Set the OpenGL context, and window callbacks
   glfwMakeContextCurrent(window);
   glfwSetWindowSizeCallback(window, windowSizeCallback);
   glfwSetMonitorCallback(monitorCallback);
   glfwSetWindowFocusCallback(window, focusCallback);
   glfwSetKeyCallback(window, keyCallback);
   glfwSetMouseButtonCallback(window, mouseClickCallback);
   glfwSetCursorPosCallback(window, mouseMotionCallback);

#ifdef _WIN32
   // Initialize GLEW
   glewExperimental = true;
   int glewInitRes = glewInit();
   ASSERT(glewInitRes == GLEW_OK, "Unable to init glew");
#endif

   // Enable vsync
   glfwSwapInterval(1);

   // Load the audio system
   audio = std::make_shared<Audio>();
   audio->systemInit();

   // Prepare for rendering (sets up OpenGL stuff)
   renderer.prepare();

   // Load the scene
   loadLevel("mainlevel");

   // Load sounds
   audio->loadSound("Restoration.ogg", true);
   audio->loadSound("jumpGrunt1.wav", false);
   audio->loadSound("jumpGrunt2.wav", false);
   audio->loadSound("jumpGrunt3.wav", false);
   audio->loadSound("shooting2.ogg", false);
   audio->loadSound("win.wav", false);
   audio->loadSound("damage2.ogg", false);

   // Timing values
   double lastTime = glfwGetTime();
   const double dt = 1.0 / 60.0;
   double accumulator = dt;
   // Game loop
   while (!glfwWindowShouldClose(window) && !scene->isGameOver()) {
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
   Loader::resetSingleton();

   audio->cleanUp();

   // Clean up GLFW
   glfwDestroyWindow(window);
   glfwTerminate();

   // Done!
   exit(EXIT_SUCCESS);
}