// Fancy assertions
#include "FancyAssert.h"

// OpenGL / GLFW
#include "GLIncludes.h"

#include "Camera.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Utils.h"

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

typedef struct {
   glm::vec3 ambient, diffuse, specular, emission;
   float shininess;
} Material;

static Camera camera;

static Light getLight() {
   Light light;

   light.position = glm::vec3(0.0f, 0.5f, 0.5f);
   light.color = glm::vec3(0.7f, 0.3f, 0.3f);
   light.constFalloff = 0.1f;
   light.linearFalloff = 0.005f;
   light.squareFalloff = 0.001f;

   return light;
}

static Material getMaterial() {
   Material material;

   glm::vec3 baseColor(0.65f, 0.0f, 1.0f);

   material.ambient = baseColor * 0.2f;
   material.diffuse = baseColor * 0.4f;
   material.specular = glm::vec3(0.4f);
   material.emission = baseColor * 0.0f;
   material.shininess = 200.0f;

   return material;
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

static ShaderProgram *program = NULL;

static void focusCallback(GLFWwindow* window, GLint focused) {
   if (focused && program) {
      program->disable();
      delete program;

      Shader vertShader(GL_VERTEX_SHADER, "shaders/phong_vert.glsl");
      Shader fragShader(GL_FRAGMENT_SHADER, "shaders/phong_frag.glsl");

      program = new ShaderProgram();
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
   window = glfwCreateWindow(width, height, "Simple example", NULL, NULL);
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

   Shader vertShader(GL_VERTEX_SHADER, "shaders/phong_vert.glsl");
   Shader fragShader(GL_FRAGMENT_SHADER, "shaders/phong_frag.glsl");

   program = new ShaderProgram();
   program->attach(vertShader);
   program->attach(fragShader);
   program->link();
   program->use();

   glClearColor(0.0, 0.0, 0.0, 0.0);

   ///////////////////////////////////////////////////

   glm::mat4 modelMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -1.0f));

   GLint uModelMatrix = program->addUniform("uModelMatrix");
   GLint uViewMatrix = program->addUniform("uViewMatrix");
   GLint uProjMatrix = program->addUniform("uProjMatrix");
   GLint uNormalMatrix = program->addUniform("uNormalMatrix");

   GLint aPosition = program->addAttribute(POSITION, "aPosition");
   GLint aNormal = program->addAttribute(NORMAL, "aNormal");

   GLint uNumLights = program->addUniform("uNumLights");
   GLint uCameraPos = program->addUniform("uCameraPos");

   // Light
   GLint uLightPos = program->addUniform("uLights[0].position");
   GLint uLightColor = program->addUniform("uLights[0].color");
   GLint uLightConst = program->addUniform("uLights[0].constFalloff");
   GLint uLightLinear = program->addUniform("uLights[0].linearFalloff");
   GLint uLightSquare = program->addUniform("uLights[0].squareFalloff");
   
   // Material
   GLint uMaterialAmbient = program->addUniform("uMaterial.ambient");
   GLint uMaterialDiffuse = program->addUniform("uMaterial.diffuse");
   GLint uMaterialSpecular = program->addUniform("uMaterial.specular");
   GLint uMaterialEmission = program->addUniform("uMaterial.emission");
   GLint uMaterialShininess = program->addUniform("uMaterial.shininess");

   float vertices[] = {
      0.0f,  0.5f, 0.0f, // Vertex 1 (X, Y)
      0.5f, -0.5f, 0.0f, // Vertex 2 (X, Y)
      -0.5f, -0.5f, 0.0f  // Vertex 3 (X, Y)
   };
   GLuint vbo;
   glGenBuffers(1, &vbo); // Generate 1 buffer
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   float normals[] = {
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f
   };
   GLuint nbo;
   glGenBuffers(1, &nbo); // Generate 1 buffer
   glBindBuffer(GL_ARRAY_BUFFER, nbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), normals, GL_STATIC_DRAW);

   GLuint vao;
   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);

   Light light = getLight();
   Material material = getMaterial();

   ///////////////////////////////////////////////////

   while (!glfwWindowShouldClose(window)) {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      ////////////////////////////////////////////////

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

      // Material
      glUniform3fv(uMaterialAmbient, 1, glm::value_ptr(material.ambient));
      glUniform3fv(uMaterialDiffuse, 1, glm::value_ptr(material.diffuse));
      glUniform3fv(uMaterialSpecular, 1, glm::value_ptr(material.specular));
      glUniform3fv(uMaterialEmission, 1, glm::value_ptr(material.emission));
      glUniform1f(uMaterialShininess, material.shininess);

      modelMatrix = glm::rotate(modelMatrix, 0.03f, glm::vec3(1.0f, 0.0f, 0.0f));
      glm::mat4 normal = glm::transpose(glm::inverse(modelMatrix));
      glUniformMatrix4fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
      glUniformMatrix4fv(uViewMatrix, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
      glUniformMatrix4fv(uProjMatrix, 1, GL_FALSE, glm::value_ptr(projection));
      glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normal));

      glEnableVertexAttribArray(aPosition);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glVertexAttribPointer(aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

      glEnableVertexAttribArray(aNormal);
      glBindBuffer(GL_ARRAY_BUFFER, nbo);
      glVertexAttribPointer(aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);

      glDrawArrays(GL_TRIANGLES, 0, 3);

      glDisableVertexAttribArray(aPosition);
      glDisableVertexAttribArray(aNormal);

      ////////////////////////////////////////////////

      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   glfwDestroyWindow(window);
   glfwTerminate();
   exit(EXIT_SUCCESS);
}