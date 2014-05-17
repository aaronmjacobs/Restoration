#include "Camera.h"
#include "FBOTextureMaterial.h"
#include "GLIncludes.h"
#include "GLMIncludes.h"
#include "Light.h"
#include "Loader.h"
#include "Mesh.h"
#include "Model.h"
#include "Renderer.h"
#include "RenderData.h"
#include "RenderState.h"
#include "Scene.h"
#include "SceneGraph.h"
#include "ShaderProgram.h"
#include "Skybox.h"
#include "SkyboxMaterial.h"

Renderer::Renderer() {
}

Renderer::~Renderer() {
}

void Renderer::prepare(SPtr<Scene> scene) {
   // Set the clear (background) color.
   glClearColor(0.0, 0.0, 0.0, 0.0);

   // Depth Buffer Setup
   glClearDepth(1.0f);
   glDepthFunc(GL_LEQUAL);
   glEnable(GL_DEPTH_TEST);

   // Back face culling
   glCullFace(GL_BACK);

   // Create frame buffer
   fb = UPtr<FrameBuffer>(new FrameBuffer);

   // TODO
   GLint m_viewport[4];
   glGetIntegerv(GL_VIEWPORT, m_viewport);
   fb->setupToTexture2D(m_viewport[2], m_viewport[3]);

   SPtr<Loader> loader = Loader::getInstance();
   Json::Value root;

   SPtr<ShaderProgram> fboProgram = loader->loadShaderProgram(nullptr, "fbo");
   SPtr<FBOTextureMaterial> fboMaterial = std::make_shared<FBOTextureMaterial>("fbo", fboProgram, *fb);
   SPtr<Mesh> planeMesh = std::make_shared<Mesh>("data/meshes/plane.obj");
   plane = UPtr<Model>(new Model(fboMaterial, planeMesh));
}

void Renderer::onWindowSizeChange(int width, int height) {
   //fb->setupToTexture2D(width, height); // TODO State cleanup
}

namespace {

RenderData _renderData;

void setRenderData(RenderData &data) {
   _renderData = data;
}

// Function that draws a SceneObject
void draw(SceneObject &obj) {
   obj.draw(_renderData);
}

} // namespace

void Renderer::prepareStencilDraw() {
   fb->applyFBO();
   glEnable(GL_STENCIL_TEST);
   // disable color and depth buffers
   glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
   glDepthMask(GL_FALSE);

   glStencilFunc(GL_NEVER, 1, 0xFF); // never pass stencil test
   glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);  // replace stencil buffer values to ref=1
   glStencilMask(0xFF); // stencil buffer free to write
   glClear(GL_STENCIL_BUFFER_BIT);  // first clear stencil buffer by writing default stencil value (0) to all of stencil buffer.
   //now draw stencil shape at stencil shape pixel locations in stencil buffer replace stencil buffer values to ref = 1

   renderData.setRenderState(STENCIL_STATE);
}

void Renderer::prepareLightDraw() {
   // enable color and depth buffers.
   glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
   glDepthMask(GL_TRUE);

   // no more modifying of stencil buffer on stencil and depth pass.
   glStencilMask(0x00);
   // can also be achieved by glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

   // stencil test: only pass stencil test at stencilValue == 1 (Assuming depth test would pass.)
   // and write actual content to depth and color buffer only at stencil shape locations.
   glStencilFunc(GL_EQUAL, 1, 0xFF);

   renderData.setRenderState(LIGHTWORLD_STATE);
}

void Renderer::prepareDarkDraw() {
   glDisable(GL_STENCIL_TEST);
   fb->disableFBO();

   renderData.setRenderState(DARKWORLD_STATE);
}

void Renderer::render(Scene &scene) {
   // Clear the render buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   SPtr<Camera> camera = scene.getCamera().lock();
   if (!camera) {
      return;
   }

   // Grab the view matrix
   glm::mat4 viewMatrix = camera->getViewMatrix();

   // Set up the matrices and lights
   const unsigned int numLights = (unsigned int)scene.getLights().size();
   glm::vec3 cameraPos = camera->getPosition();
   unsigned int lightIndex;
   for (WPtr<ShaderProgram> wShaderProgram : scene.getShaderPrograms()) {
      SPtr<ShaderProgram> shaderProgram = wShaderProgram.lock();
      if (!shaderProgram) {
         continue;
      }

      shaderProgram->use();

      // Projection matrix
      GLint uProjMatrix = shaderProgram->getUniform("uProjMatrix");
      glUniformMatrix4fv(uProjMatrix, 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));

      // View matrix
      GLint uViewMatrix = shaderProgram->getUniform("uViewMatrix");
      glUniformMatrix4fv(uViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

      // Number of lights
      GLuint uNumLights = shaderProgram->getUniform("uNumLights");
      glUniform1i(uNumLights, numLights);

      // Camera position
      GLint uCameraPos = shaderProgram->getUniform("uCameraPos");
      glUniform3fv(uCameraPos, 1, glm::value_ptr(cameraPos));

      // Lights
      lightIndex = 0;
      for (WPtr<Light> wLight : scene.getLights()) {
         SPtr<Light> light = wLight.lock();
         if (!light) {
            continue;
         }

         light->draw(*shaderProgram, lightIndex);
         ++lightIndex;
      }
   }

   // Render items to the stencil buffer
   prepareStencilDraw();
   setRenderData(renderData);
   scene.getSceneGraph()->forEach(draw);

   // Render each item in the scene (to frame buffer object) - clear color should be transparent
   prepareLightDraw();

   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   scene.getLightSkybox()->renderSkybox(renderData);

   setRenderData(renderData);
   scene.getSceneGraph()->forEach(draw);

   // Do any post processing on the light world buffer
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_BLEND);
   // Render each item in the scene (to color buffer)
   prepareDarkDraw();

   scene.getDarkSkybox()->renderSkybox(renderData);

   setRenderData(renderData);
   scene.getSceneGraph()->forEach(draw);

   // Draw light scene as textured quad over the dark scene with alpha blending enabled
   SPtr<ShaderProgram> program = plane->getMaterial()->getShaderProgram();
   program->use();
   GLint uProjMatrix = program->getUniform("uProjMatrix");
   glm::mat4 orthographic = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
   glUniformMatrix4fv(uProjMatrix, 1, GL_FALSE, glm::value_ptr(orthographic));
   plane->draw(renderData);
   glDisable(GL_BLEND);
}
