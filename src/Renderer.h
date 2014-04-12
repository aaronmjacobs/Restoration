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
   std::list<LightRef> lights;
   std::list<ShaderProgramRef> shaderPrograms;

public:
   Renderer();
   ~Renderer();
   void addLight(LightRef light);
   void addShaderProgram(ShaderProgramRef shaderProgram);
   void render(SceneGraph *scene);
};

#endif