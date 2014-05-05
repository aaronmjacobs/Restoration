#ifndef RENDERER_H
#define RENDERER_H

#include "GLMIncludes.h"
#include "MatrixStack.h"

class Scene;

/**
 * Manages the rendering of a scene.
 */
class Renderer {
protected:
   /**
    * Matrix stack of the model matrix.
    */
   MatrixStack modelMatrixStack;

public:
   /**
    * Constructs a renderer for a window with the given width and height.
    */
   Renderer();

   /**
    * Does cleanup.
    */
   virtual ~Renderer();

   /**
    * Prepares the renderer for use, making any necessary OpenGL calls.
    */
   void prepare();

   /**
    * Renders the given scene.
    */
   void render(Scene &scene);
};

#endif
