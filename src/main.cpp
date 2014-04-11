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

typedef struct {
   glm::vec3 position, color;
   float constFalloff, linearFalloff, squareFalloff;
} Light;

static Camera camera;

static Light getLight() {
   Light light;

   light.position = glm::vec3(0.0f, 1.0f, 1.0f);
   light.color = glm::vec3(0.7f, 0.3f, 0.3f);
   light.constFalloff = 0.1f;
   light.linearFalloff = 0.005f;
   light.squareFalloff = 0.001f;

   return light;
}

namespace Game {

static void testGlError(const char *message) {
   GLenum error = glGetError();
   ASSERT(error == GL_FALSE, "%s: %d", message, error);
}

} // namespace game

static void errorCallback(int error, const char* description) {
   ASSERT(false, "Error %d: %s", error, description);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
   if (action == GLFW_PRESS) {
      if (key == GLFW_KEY_ESCAPE) {
         glfwSetWindowShouldClose(window, GL_TRUE);
      } else if (key == GLFW_KEY_W) {
         camera.fly(0.1f);
      } else if (key == GLFW_KEY_S) {
         camera.fly(-0.1f);
      } else if (key == GLFW_KEY_A) {
         camera.strafe(-0.1f);
      } else if (key == GLFW_KEY_D) {
         camera.strafe(0.1f);
      }
   }
}

static ShaderProgramRef program = NULL;

static void focusCallback(GLFWwindow* window, GLint focused) {
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

static glm::mat4 projection;
static void windowSizeCallback(GLFWwindow* window, int width, int height) {
   projection = glm::perspective(90.0f, (float)width / height, 0.1f, 100.f);
}

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

   const int width = 1280, height = 720;
   window = glfwCreateWindow(width, height, "Restoration", NULL, NULL);
   ASSERT(window, "Unable to create GLFW window");

   glfwMakeContextCurrent(window);
   glfwSetWindowSizeCallback(window, windowSizeCallback);
   glfwSetWindowFocusCallback(window, focusCallback);
   glfwSetKeyCallback(window, keyCallback);

   // Prepare projection
   windowSizeCallback(window, width, height);

#ifdef _WIN32
   ASSERT(glewInit() == GLEW_OK, "Unable to init glew");
#endif

   // Enable vsync
   glfwSwapInterval(1);

   Shader vertShader(GL_VERTEX_SHADER, "shaders/phong_vert.glsl");
   Shader fragShader(GL_FRAGMENT_SHADER, "shaders/phong_frag.glsl");

   program = ShaderProgramRef(new ShaderProgram());
   program->attach(vertShader);
   program->attach(fragShader);
   program->link();
   program->loadFields("herp.derp");
   program->use();

   glClearColor(0.0, 0.0, 0.0, 0.0);

   // Depth Buffer Setup
  glClearDepth(1.0f);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);

   ///////////////////////////////////////////////////

   glm::mat4 modelMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -1.0f));

   GLint uModelMatrix = program->getUniform("uModelMatrix");
   GLint uViewMatrix = program->getUniform("uViewMatrix");
   GLint uProjMatrix = program->getUniform("uProjMatrix");
   GLint uNormalMatrix = program->getUniform("uNormalMatrix");

   GLint uNumLights = program->getUniform("uNumLights");
   GLint uCameraPos = program->getUniform("uCameraPos");

   // Light
   GLint uLightPos = program->getUniform("uLights[0].position");
   GLint uLightColor = program->getUniform("uLights[0].color");
   GLint uLightConst = program->getUniform("uLights[0].constFalloff");
   GLint uLightLinear = program->getUniform("uLights[0].linearFalloff");
   GLint uLightSquare = program->getUniform("uLights[0].squareFalloff");

   Light light = getLight();

   ///////////////////////////////////////////////////

   Renderer renderer;
   SceneGraph sceneGraph;

   MeshRef celloMesh = MeshRef(new Mesh("assets/cello_and_stand.obj"));
   glm::vec3 baseColor(0.65f, 0.0f, 1.0f);
   MaterialRef phongMaterial = MaterialRef(new PhongMaterial(program, baseColor * 0.2f, baseColor * 0.4f, glm::vec3(0.4f), baseColor * 0.0f, 200.0f));
   ModelRef celloModel = ModelRef(new Model(phongMaterial, celloMesh));

   sceneGraph.addChild(NodeRef(new GeometryNode(&sceneGraph, "cello", celloModel)));
   NodeRef cello = sceneGraph.findNodeByName("cello");
   ASSERT(cello, "Unable to fetch cello");

   double lastTime = glfwGetTime();
   double accumulator = 0.0;
   const double dt = 1.0 / 60.0;

   while (!glfwWindowShouldClose(window)) {
      double now = glfwGetTime();
      // Cap the frame time to .25 seconds to prevent spiraling
      double frameTime = glm::min(now - lastTime, 0.25);
      lastTime = now;

      accumulator += frameTime;
      while (accumulator >= dt) {
         modelMatrix = glm::rotate(modelMatrix, 0.03f, glm::vec3(1.0f, 0.0f, 0.0f));
         sceneGraph.tick(dt);
         accumulator -= dt;
      }
      
      // Num lights
      glUniform1i(uNumLights, 1);

      // Camera position
      glUniform3fv(uCameraPos, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 1.0f)));

      // Light
      glUniform3fv(uLightPos, 1, glm::value_ptr(light.position));
      glUniform3fv(uLightColor, 1, glm::value_ptr(light.color));
      glUniform1f(uLightConst, light.constFalloff);
      glUniform1f(uLightLinear, light.linearFalloff);
      glUniform1f(uLightSquare, light.squareFalloff);

      glm::mat4 normal = glm::transpose(glm::inverse(modelMatrix));
      glUniformMatrix4fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
      glUniformMatrix4fv(uViewMatrix, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
      glUniformMatrix4fv(uProjMatrix, 1, GL_FALSE, glm::value_ptr(projection));
      glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normal));

      renderer.render(&sceneGraph);

      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   glfwDestroyWindow(window);
   glfwTerminate();
   exit(EXIT_SUCCESS);
}