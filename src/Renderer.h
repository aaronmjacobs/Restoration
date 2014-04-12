#ifndef RENDERER_H
#define RENDERER_H

#include "Light.h"
#include "MatrixStack.h"
#include "ShaderProgram.h"

#include <list>

class SceneGraph;

class Renderer {
private:
   MatrixStack modelMatrixStack;
   glm::mat4 viewMatrix;
   glm::mat4 projectionMatrix;
   float fov;
   std::list<LightRef> lights;
   std::list<ShaderProgramRef> shaderPrograms;

public:
   Renderer(int width, int height, float fov);
   ~Renderer();
   void prepare();
   void onWindowSizeChange(int width, int height);
   void addLight(LightRef light);
   void addShaderProgram(ShaderProgramRef shaderProgram);
   void render(SceneGraph *scene);
};

#endif