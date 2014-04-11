#ifndef RENDERER_H
#define RENDERER_H

#include "MatrixStack.h"

class SceneGraph;

class Renderer {
private:
   MatrixStack matrixStack;

public:
   Renderer();
   ~Renderer();
   void render(SceneGraph *scene);
};

#endif