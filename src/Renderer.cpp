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
#include "Player.h"

Renderer::Renderer() {
}

Renderer::~Renderer() {
}

void Renderer::prepare() {
   // Set the clear (background) color.
   glClearColor(0.0, 0.0, 0.0, 0.0);

   // Depth Buffer Setup
   glClearDepth(1.0f);
   glDepthFunc(GL_LEQUAL);
   glEnable(GL_DEPTH_TEST);

   // Back face culling
   glCullFace(GL_BACK);

   // Create frame buffers
   fb = UPtr<FrameBuffer>(new FrameBuffer);
   shadow = UPtr<Shadow>(new Shadow);

   // Prepare the frame buffer
   fb->setupToTexture2D();
   shadow->initialize();

   Loader& loader = Loader::getInstance();
   Json::Value root;

   shadowProgram = loader.loadShaderProgram(nullptr, "shadow");

   SPtr<ShaderProgram> fboProgram = loader.loadShaderProgram(nullptr, "fbo_blur");
   SPtr<FBOTextureMaterial> fboMaterial = std::make_shared<FBOTextureMaterial>("fbo_blur", fboProgram, *fb);
   SPtr<Mesh> planeMesh = std::make_shared<Mesh>("data/meshes/plane.obj");
   plane = UPtr<Model>(new Model(fboMaterial, planeMesh));
}

void Renderer::onWindowSizeChange(int width, int height) {
   if (fb) {
      fb->setupToTexture2D();
   }
   if (shadow) {
      shadow->initialize();
   }
}

void Renderer::onMonitorChange() {
   if (fb) {
      fb->setupToTexture2D();
   }
   if (shadow) {
      shadow->initialize();
   }
}

namespace {

struct Plane {
   float a, b, c, d;
};

enum Halfspace {
   NEGATIVE = -1,
   ON_PLANE = 0,
   POSITIVE = 1,
};

Plane planes[6];

const int CULLING_SPAN = 5; // 0 = right off screen

//Returns which halfspace a point is on in reference to a plane
Halfspace classifyPoint(const Plane & plane, const glm::vec3 &point) {
   float side = plane.a * point.x + plane.b * point.y + plane.c * point.z + plane.d;
   if (side < -CULLING_SPAN)
      return NEGATIVE;
   else if (side > CULLING_SPAN)
      return POSITIVE;
   else
      return ON_PLANE;
}

//Returns which halfspace a bounding box is on in reference to a plane, added by Aaron after he made the bounding box viewable by this
Halfspace classifyBounds(const Plane &plane, const BoundingBox &bounds) {
   if (classifyPoint(plane, glm::vec3(bounds.xMin, bounds.yMin, bounds.zMin)) >= 0
       || classifyPoint(plane, glm::vec3(bounds.xMin, bounds.yMin, bounds.zMax)) >= 0
       || classifyPoint(plane, glm::vec3(bounds.xMin, bounds.yMax, bounds.zMin)) >= 0
       || classifyPoint(plane, glm::vec3(bounds.xMin, bounds.yMax, bounds.zMax)) >= 0
       || classifyPoint(plane, glm::vec3(bounds.xMax, bounds.yMin, bounds.zMin)) >= 0
       || classifyPoint(plane, glm::vec3(bounds.xMax, bounds.yMin, bounds.zMax)) >= 0
       || classifyPoint(plane, glm::vec3(bounds.xMax, bounds.yMax, bounds.zMin)) >= 0
       || classifyPoint(plane, glm::vec3(bounds.xMax, bounds.yMax, bounds.zMax)) >= 0) {
      return POSITIVE;
   }
   return NEGATIVE;
}

//Normalizes a plane
void normalizePlane(Plane &plane) {
   float size;

   size = sqrtf(powf(plane.a, 2.f) + powf(plane.b, 2.f) + powf(plane.c, 2.f));

   plane.a /= size;
   plane.b /= size;
   plane.c /= size;
   plane.d /= size;
}

//Helper function by Aaron to visualize the matrix numbers
int coord(int col, int row) {
   return (col - 1) + (row - 1) * 4;
}

//Updates the planes for culling based on the currect view-proj matrix
void updatePlanes(glm::mat4 viewProj, bool normalize) {
   const float *matrix = glm::value_ptr(viewProj);
   int sign = 1, t = 1;

   for (int i = 0; i < 6; i++) {
      t = i/2 + 1;

      planes[i].a = matrix[coord(4,1)] + sign * matrix[coord(t, 1)];
      planes[i].b = matrix[coord(4,2)] + sign * matrix[coord(t, 2)];
      planes[i].c = matrix[coord(4,3)] + sign * matrix[coord(t, 3)];
      planes[i].d = matrix[coord(4,4)] + sign * matrix[coord(t, 4)];

      if ((i % 2) == 0 ) {
         sign *= -1;
      }
   }

   if (normalize) {
      for (int i = 0; i < 6; i++) {
         normalizePlane(planes[i]);
      }
   }
}

//Return if the object is in the view frustum
bool checkInFrustum(const SceneObject &obj) {
   for (int i = 0; i < 6; i++) {
      if (classifyBounds(planes[i], obj.getBounds()) <= 0) {
         return false;
      }
   }

   return true;
}

RenderData _renderData;

void setRenderData(RenderData &data) {
   _renderData = data;
}

// Function that draws a SceneObject
void draw(SceneObject &obj) {
   // View frustum culling
   if (checkInFrustum(obj)) {
      obj.draw(_renderData);
   }
}

} // namespace

void Renderer::prepareShadowDraw(Scene& scene) {
   // apply the shadow fbo to be drawn to.
   shadow->applyFBO();
   glEnable(GL_DEPTH_TEST);
   for (WPtr<Light> wLight : scene.getLights()) {
      SPtr<Light> light = wLight.lock();
      if (!light) {
         continue;
      }
      SPtr<Camera> camera = scene.getCamera().lock();
      if (camera) {
         SPtr<Player> player = scene.getPlayer().lock();
         if (player) {
            camera->enableShadowMode(player->getPosition());
         }

      }
   }
   renderData.setRenderState(SHADOW_STATE);
}

void Renderer::prepareStencilDraw() {
   // disable the shadow fbo
   shadow->disableFBO();

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glDrawBuffer(GL_BACK);
   glReadBuffer(GL_BACK);
   
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
      glUniformMatrix4fv(uViewMatrix, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));

      if (shaderProgram->hasUniform("uNumLights")) {
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
   }

   // Update view frustum culling planes. True or false for normalizing planes
   updatePlanes(camera->getProjectionMatrix() * camera->getViewMatrix(), true);

#ifndef NO_FBO

   // Render items into shadowmap @ light position. Need scene to get access to lights.
   prepareShadowDraw(scene);

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
      glUniformMatrix4fv(uViewMatrix, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
   }

   renderData.set("uDepthMVP", camera->getProjectionMatrix() * camera->getViewMatrix());
   renderData.set("shadowMapID", shadow->getTextureID());

   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   setRenderData(renderData);
   scene.getSceneGraph()->forEach(draw);

   camera->disableShadowMode();

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
      glUniformMatrix4fv(uViewMatrix, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
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

#endif

   // Do any post processing on the light world buffer
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_BLEND);
   // Render each item in the scene (to color buffer)
   prepareDarkDraw();

   scene.getDarkSkybox()->renderSkybox(renderData);

   setRenderData(renderData);
   scene.getSceneGraph()->forEach(draw);

#ifndef NO_FBO

   // Draw light scene as textured quad over the dark scene with alpha blending enabled
   SPtr<ShaderProgram> program = plane->getMaterial()->getShaderProgram();
   program->use();

   // Set the width and height of the viewport (for blurring)
   GLint uViewportWidth = program->getUniform("uViewportWidth");
   GLint uViewportHeight = program->getUniform("uViewportHeight");
   glUniform1i(uViewportWidth, fb->getWidth());
   glUniform1i(uViewportHeight, fb->getHeight());

   renderData.set("sh", shadow->getTextureID());
   plane->draw(renderData);

#endif

   glDisable(GL_BLEND);
}
