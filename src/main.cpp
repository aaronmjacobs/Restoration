#include "engine/Camera.h"
#include "engine/GeometryNode.h"
#include "engine/Loader.h"
#include "engine/Mesh.h"
#include "engine/Model.h"
#include "engine/Renderer.h"
#include "engine/Scene.h"
#include "engine/SceneGraph.h"
#include "engine/Shader.h"
#include "engine/ShaderProgram.h"
#include "engine/TransformNode.h"
#include "engine/IOUtils.h"

#include "serialization/Serializer.h"

#include "FirstPersonCameraController.h"
#include "PhongMaterial.h"

// Fancy assertions
#include "engine/FancyAssert.h"

// OpenGL / GLFW
#include "engine/GLIncludes.h"

// GLM
#include "engine/GLMIncludes.h"

#include "engine/lib/json/json.h"

// STL
#include <cerrno>
#include <iostream>
#include <fstream>
#include <string>

namespace {

const int WIDTH = 1280, HEIGHT = 720;
const float FOV = glm::radians(80.0f);

Scene scene(SceneGraphRef(new SceneGraph), CameraSerializer::load("camera1.json"));
Renderer renderer(WIDTH, HEIGHT, FOV);
FirstPersonCameraController cameraController(scene.getCamera());

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

   scene.onKeyEvent(key, action);
}

void mouseClickCallback(GLFWwindow *window, int button, int action, int mods) {
   scene.onMouseButtonEvent(button, action);
}

void mouseMotionCallback(GLFWwindow *window, double xPos, double yPos) {
   scene.onMouseMotionEvent(xPos, yPos);
}

void focusCallback(GLFWwindow* window, GLint focused) {
   if (focused) {
      scene.onWindowFocusGained();
   }
}

void windowSizeCallback(GLFWwindow* window, int width, int height) {
   renderer.onWindowSizeChange(width, height);
}

void test() {
   scene.addInputListener(&cameraController);
   scene.addTickListener(&cameraController);

   /*ShaderRef vertShader(new Shader("phong_vert.json", GL_VERTEX_SHADER, "shaders/phong_vert.glsl"));
   ShaderRef fragShader(new Shader("phong_frag.json", GL_FRAGMENT_SHADER, "shaders/phong_frag.glsl"));

   Serializer::save(*vertShader);
   Serializer::save(*fragShader);

   ShaderProgramRef program = ShaderProgramRef(new ShaderProgram("phong.json"));
   program->attach(vertShader);
   program->attach(fragShader);
   program->compileShaders();
   program->link();

   // TODO Load fields via some sort of file
   program->addUniform("uModelMatrix");
   program->addUniform("uViewMatrix");
   program->addUniform("uProjMatrix");
   program->addUniform("uNormalMatrix");
   program->addAttribute("aPosition");
   program->addAttribute("aNormal");
   program->addUniform("uNumLights");
   program->addUniform("uCameraPos");
   program->addUniform("uLights[0].position");
   program->addUniform("uLights[0].color");
   program->addUniform("uLights[0].constFalloff");
   program->addUniform("uLights[0].linearFalloff");
   program->addUniform("uLights[0].squareFalloff");
   program->addUniform("uMaterial.ambient");
   program->addUniform("uMaterial.diffuse");
   program->addUniform("uMaterial.specular");
   program->addUniform("uMaterial.emission");
   program->addUniform("uMaterial.shininess");

   Serializer::save(*program);*/

   //ShaderProgramRef program = ShaderProgramSerializer::load("phong.json");
   LightRef light = LightSerializer::load("light1.json");

   //LightRef light(new Light("light1.json", glm::vec3(0.0f, 0.5f, 0.5f), glm::vec3(0.3f), 0.1f, 0.005f, 0.001f));
   scene.addLight(light);

   Serializer::save(*light);

   MeshRef celloMesh = MeshSerializer::load("cello.json");

   //glm::vec3 baseColor(0.65f, 0.0f, 1.0f);
   //MaterialRef phongMaterial(new PhongMaterial("phong1.json", program, baseColor * 0.2f, baseColor * 0.4f, glm::vec3(0.4f), baseColor * 0.0f, 300.0f));
   MaterialRef phongMaterial = PhongMaterialSerializer::load("phong1.json");
   ModelRef celloModel(new Model(phongMaterial, celloMesh));

   NodeRef celloNode(new GeometryNode("cello", celloModel));
   celloNode->translateBy(glm::vec3(0.0f, 0.0f, -2.0f));
   celloNode->rotateBy(glm::angleAxis(-0.25f, glm::vec3(1.0f, 0.0f, 0.0f)));
   scene.getSceneGraph()->addChild(celloNode);

   NodeRef transformNode(new TransformNode("move"));
   transformNode->translateBy(glm::vec3(0.0f, -2.0f, 0.0f));
   transformNode->rotateBy(glm::angleAxis(-1.57f, glm::vec3(1.0f, 0.0f, 0.0f)));
   celloNode->addChild(transformNode);

   //glm::vec3 baseColor2(0.2f, 0.6f, 0.5f);
   //MaterialRef phongMaterial2(new PhongMaterial("phong2.json", program, baseColor2 * 0.1f, baseColor2 * 0.2f, baseColor2 * 0.6f, baseColor2 * 0.0f, 20.0f));
   MaterialRef phongMaterial2 = PhongMaterialSerializer::load("phong2.json");

   ModelRef celloModel2(new Model(phongMaterial2, celloMesh));
   NodeRef celloNode2(new GeometryNode("cello2", celloModel2));
   transformNode->addChild(celloNode2);

   scene.addShaderProgram(phongMaterial->getShaderProgram()); // TODO Automatic somehow?
   scene.addShaderProgram(phongMaterial2->getShaderProgram()); // TODO Automatic somehow?

   //Serializer::save(*phongMaterial);
   //Serializer::save(*phongMaterial2);
}

} // namespace

int main(int argc, char *argv[]) {
   // Initialize GLFW
   GLFWwindow* window;
   glfwSetErrorCallback(errorCallback);
   ASSERT(glfwInit(), "Unable to init glfw");

#ifdef __APPLE__
   // Set hints to use OpenGL 3.3
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

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

   // Prepare for rendering (sets up OpenGL stuff)
   renderer.prepare();

   test();

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
         scene.tick(dt);
         accumulator -= dt;
      }

      // Render the scene
      renderer.render(&scene);

      // Display the rendered scene
      glfwSwapBuffers(window);

      // Poll for events
      glfwPollEvents();
   }

   // Clean up GLFW
   glfwDestroyWindow(window);
   glfwTerminate();

   // Done!
   exit(EXIT_SUCCESS);
}