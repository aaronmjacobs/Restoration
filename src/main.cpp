// Fancy assertions
#include "FancyAssert.h"

// OpenGL / GLFW
#include "GLIncludes.h"

#include "Camera.h"
#include "Mesh.h"
#include "Model.h"
#include "Loader.h"
#include "PhongMaterial.h"
#include "Renderer.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Utils.h"

#include "SceneGraph.h"
#include "GeometryNode.h"

// GLM
#include "GLMIncludes.h"

// STL
#include <cerrno>
#include <iostream>
#include <string>

namespace {

const int WIDTH = 1280, HEIGHT = 720;
const float FOV = 90.0f;

SceneGraph sceneGraph;
Renderer renderer(WIDTH, HEIGHT, FOV);

void testGlError(const char *message) {
   GLenum error = glGetError();
   ASSERT(error == GL_FALSE, "%s: %d", message, error);
}

void errorCallback(int error, const char* description) {
   ASSERT(false, "Error %d: %s", error, description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
   if (action == GLFW_PRESS) {
      if (key == GLFW_KEY_ESCAPE) {
         glfwSetWindowShouldClose(window, GL_TRUE);
      } else if (key == GLFW_KEY_W) {
         sceneGraph.getCamera()->fly(0.1f);
      } else if (key == GLFW_KEY_S) {
         sceneGraph.getCamera()->fly(-0.1f);
      } else if (key == GLFW_KEY_A) {
         sceneGraph.getCamera()->strafe(-0.1f);
      } else if (key == GLFW_KEY_D) {
         sceneGraph.getCamera()->strafe(0.1f);
      }
   }
}

ShaderProgramRef program = NULL;

void focusCallback(GLFWwindow* window, GLint focused) {
   if (focused && program) {
      program->disable();

      Shader vertShader(GL_VERTEX_SHADER, "shaders/phong_vert.glsl");
      Shader fragShader(GL_FRAGMENT_SHADER, "shaders/phong_frag.glsl");

      program = ShaderProgramRef(new ShaderProgram());
      program->attach(vertShader);
      program->attach(fragShader);
      program->link();
      program->use();
   }
}

void windowSizeCallback(GLFWwindow* window, int width, int height) {
   renderer.onWindowSizeChange(width, height);
}

void test() {
   Shader vertShader(GL_VERTEX_SHADER, "shaders/phong_vert.glsl");
   Shader fragShader(GL_FRAGMENT_SHADER, "shaders/phong_frag.glsl");

   program = ShaderProgramRef(new ShaderProgram());
   program->attach(vertShader);
   program->attach(fragShader);
   program->link();
   program->loadFields("herp.derp");
   program->use();

   renderer.addLight(LightRef(new Light(glm::vec3(0.0f, 0.5f, 0.5f), glm::vec3(0.2f), 0.1f, 0.005f, 0.001f)));
   renderer.addShaderProgram(program);
   MeshRef celloMesh = MeshRef(new Mesh("assets/cello_and_stand.obj"));
   glm::vec3 baseColor(0.65f, 0.0f, 1.0f);
   MaterialRef phongMaterial = MaterialRef(new PhongMaterial(program, baseColor * 0.2f, baseColor * 0.4f, glm::vec3(0.4f), baseColor * 0.0f, 200.0f));
   ModelRef celloModel = ModelRef(new Model(phongMaterial, celloMesh));

   NodeRef celloNode(new GeometryNode(&sceneGraph, "cello", celloModel));
   celloNode->translate(glm::vec3(0.0f, 0.0f, -2.0f));
   sceneGraph.addChild(celloNode);
   NodeRef cello = sceneGraph.findNodeByName("cello");
   ASSERT(cello, "Unable to fetch cello");
}

}; // namespace

int main(int argc, char *argv[]) {
   GLFWwindow* window;
   glfwSetErrorCallback(errorCallback);
   ASSERT(glfwInit(), "Unable to init glfw");

#ifdef __APPLE__
   // Set hints to use OpenGL 3.3
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   //glfwWindowHint(GLFW_SAMPLES, 16);
#endif

   window = glfwCreateWindow(WIDTH, HEIGHT, "Restoration", NULL, NULL);
   ASSERT(window, "Unable to create GLFW window");

   glfwMakeContextCurrent(window);
   glfwSetWindowSizeCallback(window, windowSizeCallback);
   glfwSetWindowFocusCallback(window, focusCallback);
   glfwSetKeyCallback(window, keyCallback);

#ifdef _WIN32
   ASSERT(glewInit() == GLEW_OK, "Unable to init glew");
#endif

   // Enable vsync
   glfwSwapInterval(1);

   renderer.prepare();

   test();
   NodeRef cello = sceneGraph.findNodeByName("cello");
   ASSERT(cello, "Unable to fetch cello");

   double lastTime = glfwGetTime();
   double accumulator = 0.0;
   const double dt = 1.0 / 60.0;

   while (!glfwWindowShouldClose(window)) {
      // Calculate the frame time
      double now = glfwGetTime();
      double frameTime = glm::min(now - lastTime, 0.25); // Cap the frame time to .25 seconds to prevent spiraling
      lastTime = now;

      // Update the scene
      accumulator += frameTime;
      while (accumulator >= dt) {
         sceneGraph.tick(dt);
         accumulator -= dt;
      }

      // Render the scene
      renderer.render(&sceneGraph);

      // Display the rendered scene
      glfwSwapBuffers(window);

      // Poll for events
      glfwPollEvents();
   }

   glfwDestroyWindow(window);
   glfwTerminate();
   exit(EXIT_SUCCESS);
}