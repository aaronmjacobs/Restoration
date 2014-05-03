// Fancy assertions
#include "FancyAssert.h"

// OpenGL / GLFW
#include "GLIncludes.h"

// GLM
#include "GLMIncludes.h"

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

SPtr<Scene> scene;
Renderer renderer(WIDTH, HEIGHT, FOV);
SPtr<Light> light;

void testGlError(const char *message) {
   GLenum error = glGetError();
   ASSERT(error == GL_FALSE, "%s: %d", message, error);
}

void errorCallback(int error, const char* description) {
   ASSERT(false, "Error %d: %s", error, description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
   if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
      glfwSetWindowShouldClose(window, GL_TRUE);
   }

   if (action == GLFW_PRESS && key == GLFW_KEY_R) {
      SPtr<SceneGraph> graph = scene->getSceneGraph();
      /*WPtr<SceneObject> derpObject = graph->find("derp");
      SPtr<SceneObject> sDerpObject = derpObject.lock();
      if (sDerpObject) {
         graph->remove(sDerpObject);
      }*/
      graph->remove(light);
      scene->removeLight(light);
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
   renderer.onWindowSizeChange(width, height);
}

void addRemoveTest() {
   SPtr<SceneGraph> graph = scene->getSceneGraph();

   SPtr<Mesh> mesh = std::make_shared<Mesh>("data/meshes/cello_and_stand.obj");
   SPtr<Loader> loader = Loader::getInstance();
   SPtr<Material> material2 = loader->loadMaterial(scene, "otherMaterial");
   SPtr<Model> model = std::make_shared<Model>(material2, mesh);

   std::string derp = "derp";
   for (int i = 0; i < 500000; ++i) {
      graph->add(std::make_shared<Geometry>(scene, model, derp + std::to_string(i)));
   }
   int i;
   std::cin >> i;
   for (int i = 0; i < 500000; ++i) {
      WPtr<SceneObject> wObj = graph->find(derp + std::to_string(i));
      SPtr<SceneObject> obj = wObj.lock();
      graph->remove(obj);
   }
}

void test() {
   SPtr<SceneGraph> graph = scene->getSceneGraph();

   /*SPtr<Camera> camera = std::make_shared<Camera>(scene, "camera");
   camera->fly(-5.0f);
   scene->setCamera(camera);
   graph->add(camera);

   SPtr<Light> light = std::make_shared<Light>(scene, glm::vec3(0.3f), 0.1f, 0.005f, 0.001f);
   light->setPosition(glm::vec3(0.0f, 5.0f, 5.0f));
   scene->addLight(light);
   graph->add(light);*/

   SPtr<Mesh> mesh = std::make_shared<Mesh>("data/meshes/cello_and_stand.obj");

   /*SPtr<Shader> vertShader = std::make_shared<Shader>(GL_VERTEX_SHADER, "data/shaders/phong_vert.glsl");
   SPtr<Shader> fragShader = std::make_shared<Shader>(GL_FRAGMENT_SHADER, "data/shaders/phong_frag.glsl");
   SPtr<ShaderProgram> shaderProgram = std::make_shared<ShaderProgram>("phong");
   shaderProgram->attach(vertShader);
   shaderProgram->attach(fragShader);
   shaderProgram->compileShaders();
   shaderProgram->link();
   scene->addShaderProgram(shaderProgram);

   shaderProgram->addAttribute("aPosition");
   shaderProgram->addAttribute("aNormal");
   shaderProgram->addUniform("uProjMatrix");
   shaderProgram->addUniform("uViewMatrix");
   shaderProgram->addUniform("uModelMatrix");
   shaderProgram->addUniform("uNormalMatrix");
   shaderProgram->addUniform("uNumLights");
   shaderProgram->addUniform("uCameraPos");
   shaderProgram->addUniform("uMaterial.ambient");
   shaderProgram->addUniform("uMaterial.diffuse");
   shaderProgram->addUniform("uMaterial.specular");
   shaderProgram->addUniform("uMaterial.emission");
   shaderProgram->addUniform("uMaterial.shininess");
   shaderProgram->addUniform("uLights[0].position");
   shaderProgram->addUniform("uLights[0].color");
   shaderProgram->addUniform("uLights[0].constFalloff");
   shaderProgram->addUniform("uLights[0].linearFalloff");
   shaderProgram->addUniform("uLights[0].squareFalloff");

   shaderProgram->addUniform("uLights[1].position");
   shaderProgram->addUniform("uLights[1].color");
   shaderProgram->addUniform("uLights[1].constFalloff");
   shaderProgram->addUniform("uLights[1].linearFalloff");
   shaderProgram->addUniform("uLights[1].squareFalloff");

   shaderProgram->addUniform("uLights[2].position");
   shaderProgram->addUniform("uLights[2].color");
   shaderProgram->addUniform("uLights[2].constFalloff");
   shaderProgram->addUniform("uLights[2].linearFalloff");
   shaderProgram->addUniform("uLights[2].squareFalloff");

   shaderProgram->addUniform("uLights[3].position");
   shaderProgram->addUniform("uLights[3].color");
   shaderProgram->addUniform("uLights[3].constFalloff");
   shaderProgram->addUniform("uLights[3].linearFalloff");
   shaderProgram->addUniform("uLights[3].squareFalloff");

   shaderProgram->addUniform("uLights[4].position");
   shaderProgram->addUniform("uLights[4].color");
   shaderProgram->addUniform("uLights[4].constFalloff");
   shaderProgram->addUniform("uLights[4].linearFalloff");
   shaderProgram->addUniform("uLights[4].squareFalloff");

   shaderProgram->addUniform("uLights[5].position");
   shaderProgram->addUniform("uLights[5].color");
   shaderProgram->addUniform("uLights[5].constFalloff");
   shaderProgram->addUniform("uLights[5].linearFalloff");
   shaderProgram->addUniform("uLights[5].squareFalloff");

   shaderProgram->addUniform("uLights[6].position");
   shaderProgram->addUniform("uLights[6].color");
   shaderProgram->addUniform("uLights[6].constFalloff");
   shaderProgram->addUniform("uLights[6].linearFalloff");
   shaderProgram->addUniform("uLights[6].squareFalloff");

   shaderProgram->addUniform("uLights[7].position");
   shaderProgram->addUniform("uLights[7].color");
   shaderProgram->addUniform("uLights[7].constFalloff");
   shaderProgram->addUniform("uLights[7].linearFalloff");
   shaderProgram->addUniform("uLights[7].squareFalloff");

   shaderProgram->addUniform("uLights[8].position");
   shaderProgram->addUniform("uLights[8].color");
   shaderProgram->addUniform("uLights[8].constFalloff");
   shaderProgram->addUniform("uLights[8].linearFalloff");
   shaderProgram->addUniform("uLights[8].squareFalloff");

   shaderProgram->addUniform("uLights[9].position");
   shaderProgram->addUniform("uLights[9].color");
   shaderProgram->addUniform("uLights[9].constFalloff");
   shaderProgram->addUniform("uLights[9].linearFalloff");
   shaderProgram->addUniform("uLights[9].squareFalloff");*/


   //IOUtils::save(*shaderProgram, shaderProgram->getJsonFileName());

   //SPtr<ShaderProgram> shaderProgram2 = ShaderProgramDeserializer::deserialize("phong");
   //IOUtils::save(*shaderProgram2, "phong2");

   //glm::vec3 baseColor(0.65f, 0.0f, 1.0f);
   //SPtr<Material> material = std::make_shared<PhongMaterial>("testMaterial", shaderProgram2,
   //      baseColor * 0.2f, baseColor * 0.4f, glm::vec3(0.4f), baseColor * 0.0f, 300.0f);
   //IOUtils::save(*material, material->getJsonFileName());

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
}

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

   // Create the scene
   //scene = std::make_shared<Scene>("");
   //scene->setSceneGraph(std::make_shared<FlatSceneGraph>());
   double start = glfwGetTime();
   SPtr<Loader> loader = Loader::getInstance();
   scene = loader->loadScene("testScene");
   std::cout << "Loading time: " << (glfwGetTime() - start) << std::endl;

   // Prepare for rendering (sets up OpenGL stuff)
   renderer.prepare();

   test();
   //addRemoveTest();

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

   // Clean up GLFW
   glfwDestroyWindow(window);
   glfwTerminate();

   // Done!
   exit(EXIT_SUCCESS);
}